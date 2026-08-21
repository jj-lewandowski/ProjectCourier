package jmap

type Request struct {
	Using       []string     `json:"using"`
	MethodCalls []Invocation `json:"methodCalls"`
}
