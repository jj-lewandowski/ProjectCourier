package jmap

import (
	"encoding/json"
	"fmt"
)

type Invocation struct {
	Name string
	Args any
	ID   string
}

func (i *Invocation) MarshalJSON() ([]byte, error) {
	j := []any{
		i.Name,
		i.Args,
		i.ID,
	}
	return json.Marshal(j)
}

func (i *Invocation) UnmarshalJSON(data []byte) error {
	raw := []json.RawMessage{}

	err := json.Unmarshal(data, &raw)
	if err != nil {
		return err
	}
	if len(raw) != 3 {
		fmt.Println("Not enough values in invocation")
	}
	if err := json.Unmarshal(raw[0], &i.Name); err != nil {
		return err
	}
	calledMethod, ok := method[i.Name]
	if !ok {
		return fmt.Errorf("Method '%s' not recognized", i.Name)
	}
	i.Args = calledMethod()
	if err := json.Unmarshal(raw[1], i.Args); err != nil {
		return err
	}
	if err := json.Unmarshal(raw[2], &i.ID); err != nil {
		return err
	}
	return nil

}
