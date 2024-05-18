package main

import (
	"fmt"
	"sort"
	"strconv"
)

type client struct {
	ticket   string
	duration int
}

type Queue struct {
	NumberOfWindows int
	windows         [][]client
	visitors        []client
}

func NewQueue(numWindows int) *Queue {
	return &Queue{
		NumberOfWindows: numWindows,
		windows:         make([][]client, numWindows),
	}
}

func (q *Queue) Enqueue(duration int, ticketNumber int) {
	ticket := "T" + strconv.Itoa(ticketNumber)
	q.visitors = append(q.visitors, client{ticket: ticket, duration: duration})
	fmt.Println(ticket)
}

func (q *Queue) Distribute() {
	load := make([]int, q.NumberOfWindows)

	// Сортировка посетителей по убыванию продолжительности для оптимизации распределения максимальной нагрузки
	sort.Slice(q.visitors, func(i, j int) bool {
		return q.visitors[i].duration > q.visitors[j].duration
	})

	for _, v := range q.visitors {
		minWindow := 0
		for i := 1; i < len(load); i++ {
			if load[i] < load[minWindow] {
				minWindow = i
			}
		}
		load[minWindow] += v.duration
		q.windows[minWindow] = append(q.windows[minWindow], v)
	}

	for i, window := range q.windows {
		fmt.Printf("Окно %d (", i+1)
		time := 0
		NotPrinted := true
		for _, v := range window {
			if !NotPrinted {
				fmt.Print(", ")
			}
			NotPrinted = false
			fmt.Print(v.ticket)
			time += v.duration
		}
		fmt.Printf(") %d минут\n", time)

	}
}

func main() {
	var NumberOfWindows int
	fmt.Print("Введите кол-во окон: ")
	fmt.Scan(&NumberOfWindows)
	queue := NewQueue(NumberOfWindows)

	var command string
	ticketNumber := 1
	for {
		fmt.Scan(&command)
		if command == "ENQUEUE" {
			var duration int
			fmt.Scan(&duration)
			queue.Enqueue(duration, ticketNumber)
			ticketNumber++
		} else if command == "DISTRIBUTE" {
			if ticketNumber != 1 {
				queue.Distribute()
				break
			} else {
				fmt.Print("Ошибка! Вы не добавили никого в очередь!")
			}

		} else if command == "exit" {
			return
		}
	}
}
