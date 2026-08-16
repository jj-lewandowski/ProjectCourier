package main

import (
	"encoding/json"
	"log"
	"net/http"
)

type Capabilities struct {
	MaxSizeUpload        uint     `json:"maxSizeUpload"`
	MaxConcurrentUpload  uint     `json:"maxConcurrentUpload"`
	MaxSizeRequest       uint     `json:"maxSizeRequest"`
	MaxConcurrentRequest uint     `json:"maxConcurrentRequest"`
	MaxCallsInRequest    uint     `json:"maxCallsInRequest"`
	MaxObjectsInGet      uint     `json:"maxObjectsInGet"`
	MaxObjectsInSet      uint     `json:"maxObjectsInSet"`
	CollationAlgorithms  []string `json:"collationAlgorithms"`
}
type Account struct {
	Name                string   `json:"name"`
	IsPersonal          bool     `json:"isPersonal"`
	IsReadOnly          bool     `json:"isReadOnly"`
	AccountCapabilities []string `json:"accountCapabilities"`
}
type Session struct {
	Capabilities    map[string]Capabilities `json:"capabilities"`
	Accounts        map[string]Account      `json:"accounts"`
	PrimaryAccounts map[string]string       `json:"primaryAccounts"`
	Username        string                  `json:"username"`
	APIURL          string                  `json:"apiUrl"`
	DownloadURL     string                  `json:"downloadUrl"`
	UploadURL       string                  `json:"uploadUrl"`
	EventSourceURL  string                  `json:"eventSourceUrl"`
	State           string                  `json:"state"`
}

func main() {
	http.HandleFunc("/.well-known/jmap", func(w http.ResponseWriter, r *http.Request) {
		w.Header().Set("Content-Type", "application/json")
		session := Session{
			Capabilities: map[string]Capabilities{
				"urn:ietf:params:jmap:core": {
					MaxSizeUpload:        50_000_000,
					MaxConcurrentUpload:  4,
					MaxSizeRequest:       10_000_000,
					MaxConcurrentRequest: 4,
					MaxCallsInRequest:    16,
					MaxObjectsInGet:      500,
					MaxObjectsInSet:      500,
					CollationAlgorithms:  []string{"i;ascii-casemap"},
				},
			},
			Username: "test",
			State:    "1",
			Accounts: map[string]Account{
				"account1": {
					Name:       "test",
					IsPersonal: false,
					IsReadOnly: false,
				},
			},
			PrimaryAccounts: map[string]string{
				"urn:ietf:params:jmap:mail": "account1",
			},
			APIURL:         "http://localhost:8080/api",
			DownloadURL:    "http://localhost:8080/download",
			UploadURL:      "http://localhost:8080/upload",
			EventSourceURL: "http://localhost:8080/event",
		}
		encoder := json.NewEncoder(w)
		encoder.SetIndent("", "  ")
		err := encoder.Encode(session)
		if err != nil {
			http.Error(w, "encoding failed", http.StatusInternalServerError)
			return
		}
	})

	err := http.ListenAndServe(":8080", nil)
	if err != nil {
		log.Fatal(err)
	}

}
