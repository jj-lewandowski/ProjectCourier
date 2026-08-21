package jmap

type CoreEcho map[string]any
type EmailGet struct {
	ID   string
	Data string
}

var method = map[string]func() any{
	"Core/echo": func() any {
		return &CoreEcho{}
	},
	"Email/get": func() any {
		return &EmailGet{}
	},
}
