package main

import (
	"encoding/json"
	"log"
	"net/http"

	"github.com/jj-lewandowski/ProjectCourier/jmap"
)

func main() {

	http.HandleFunc("POST /api", func(w http.ResponseWriter, r *http.Request) {
		var req jmap.Request
		err := json.NewDecoder(r.Body).Decode(&req)
		if err != nil {
			http.Error(w, "decoding failed", http.StatusInternalServerError)
		}
		w.Header().Set("Content-Type", "application/json")
		encoder := json.NewEncoder(w)
		encodeErr := encoder.Encode(req.MethodCalls)
		if encodeErr != nil {
			http.Error(w, "encoding failed", http.StatusInternalServerError)
			return
		}
	})
	http.HandleFunc("GET /.well-known/jmap", func(w http.ResponseWriter, r *http.Request) {
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
