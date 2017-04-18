package main

import (
	"fmt"
	"log"

	"github.com/streadway/amqp"
)

func fadilOnError(err error, msg string) {
	if err != nil {
		log.Fatalf("%s: %s", msg, err)

		panic(fmt.Sprintf("%s: %s", msg, err))
	}
}

func main() {

	conn, err := amqp.Dial("amqp://guest:guest@localhost:5672/")
	fadilOnError(err, "Failed to connect to RabbitMQ")
	defer conn.Close()

	ch, err := conn.Channel()
	fadilOnError(err, "Failed to open a channel")
	defer ch.Close()

	q, err := ch.QueueDeclare(
		"hello", // name
		false,   // durable
		false,   // delete when unused,
		false,   // exclusive
		false,   // no-wait
		nil,     // arguments
	)
	fadilOnError(err, "Failed to decalre a queue")

	msgs, err := ch.Consume(q.Name, "", true, false, false, false, nil)
	fadilOnError(err, "Failed to register a consumer")

	forever := make(chan bool)

	go func() {
		for d := range msgs {
			log.Printf("Recevied a message: %s", d.Body)
		}
	}()

	log.Printf(" [*] Waiting for message. to exit press CTRL+C")
	<-forever
}
