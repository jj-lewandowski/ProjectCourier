package main

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
