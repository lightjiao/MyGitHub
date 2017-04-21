package main

import (
	"fmt"
	"log"
	"os"
	"time"

	"github.com/streadway/amqp"
)

func fadilOnError(err error, msg string) {
	if err != nil {
		log.Fatalf("%s: %s", msg, err)

		panic(fmt.Sprintf("%s: %s", msg, err))
	}
}

func main() {

	var msgs (<-chan amqp.Delivery)
	for true {
		conn, err := amqp.Dial("amqp://guest:guest@localhost:5672/")
		fadilOnError(err, "Failed to connect to RabbitMQ")
		defer conn.Close()

		ch, err := conn.Channel()
		fadilOnError(err, "Failed to open a channel")
		defer ch.Close()

		err = ch.ExchangeDeclare(
			"logs_topic",
			"topic",
			true,  // durable
			false, // auto-deleted
			false, // internal
			false, // no-waite
			nil,   // arguments
		)
		fadilOnError(err, "Failed to declare an exchange")

		// 重试的声明queue
		fmt.Print("Start declare queue ...")
		var q amqp.Queue
		for true {
			q, err = ch.QueueDeclare(
				"exclusive_queue", // name
				false,             // durable
				true,              // autoDelete
				false,             // exclusive
				false,             // noWait
				nil,
			)
			if err == nil {
				fmt.Printf("Decalre queue %s successful.", q.Name)
				break
			}
			time.Sleep(1000 * 1000 * 1000)
			fmt.Print("try onece... ")
			// fadilOnError(err, "Failed to declare a queue")
		}

		if len(os.Args) < 2 {
			log.Printf("Usage: %s [binding_key]...", os.Args[0])
			os.Exit(0)
		}

		for _, s := range os.Args[1:] {
			log.Printf("Binding queue %s to exchange %s with routing key %s", q.Name, "logs_topic", s)

			err = ch.QueueBind(q.Name, s, "logs_topic", false, nil)
			fadilOnError(err, "Failed to bind a queue")
		}

		// var msgs (<-chan amqp.Delivery)
		fmt.Print("start to register a consumer ...")
		msgs, err = ch.Consume(
			q.Name,
			"",
			true,
			true, // exclusive:  Don't allow other consumers on the queue
			false,
			false,
			nil,
		)
		if err == nil {
			fmt.Printf("Register consumer in queue %s successful.", q.Name)
			break
		}
		time.Sleep(1000 * 1000 * 1000)
		fmt.Print("try onece... ")
		// fadilOnError(err, "Failed to declare a queue")

	}

	forever := make(chan bool)

	go func() {
		for d := range msgs {
			log.Printf(" [x] %s", d.Body)
		}
	}()

	log.Print(" [*] Waiting for logs. To exit press CTRL+C")

	<-forever
}
