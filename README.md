# Philosophers - 42 Project

## Table of Contents
- [Introduction](#introduction)
- [Mandatory Part](#mandatory-part)
  - [Overview](#overview)
  - [How It Works](#how-it-works)
  - [Compilation and Execution](#compilation-and-execution)
- [Bonus Part](#bonus-part)
  - [Overview](#bonus-overview)
  - [Changes from Mandatory](#changes-from-mandatory)
- [Resources](#resources)
- [Author](#author)

## Introduction
The **Philosophers** project is a classic synchronization problem, often used to teach the fundamentals of threading, race conditions, and deadlock handling. The goal of the project is to simulate the behavior of philosophers sitting around a table, alternating between eating, thinking, and sleeping, while avoiding starvation and deadlocks.

## Mandatory Part

### Overview
In the mandatory part, the problem involves five philosophers sitting at a circular table with five forks. Each philosopher needs two forks to eat but can only take the fork to their left and the fork to their right. The goal is to simulate this situation using threads, ensuring no philosopher starves, and handling concurrency properly.

### How It Works
- Each philosopher is represented by a thread.
- Forks are represented as shared resources (mutexes).
- Philosophers alternate between eating, sleeping, and thinking.
- The program must avoid deadlock and ensure all philosophers have a chance to eat.

### Compilation and Execution
To compile the project, use the following command:

```bash
make
```

To run the program, execute:

```bash
./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]
```

Example:

```bash
./philo 5 800 200 200 7
```

## Bonus Part

### Bonus Overview
The bonus part adds an extra layer of complexity by using **processes** instead of threads, requiring inter-process communication mechanisms. Each philosopher is represented by a separate process, and semaphores are used to manage access to shared resources (forks).

### Changes from Mandatory
- Instead of threads, philosophers are now individual processes.
- Forks and other shared resources are controlled using semaphores.
- You must handle the creation and termination of processes properly, avoiding zombie processes.

### Compilation and Execution
To compile the bonus version, use the following command:

```bash
make bonus
```

To run the bonus program, execute:

```bash
./philo_bonus [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]
```

## Resources
- [Philosophers Visualizer](https://nafuka11.github.io/philosophers-visualizer/)
- [The Dining Philosophers - Medium Article](https://medium.com/@jalal92/the-dining-philosophers-7157cc05315)
- [Concurrency & Synchronization e-Book](https://pages.mtu.edu/~shene/NSF-3/e-Book/index.html)
- [42 Philosophers Test Cases](https://github.com/poechlauerbe/42_tests/tree/main/c03_philosophers)

## Author
**hel-omra**  
[42 Intra Profile](https://profile.intra.42.fr/users/hel-omra)
```
