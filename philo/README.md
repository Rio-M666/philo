*This project has been created as part of the 42 curriculum by mrio.*

# Philosophers

## Description

This project is an implementation of the classic **Dining Philosophers Problem**, originally formulated by Edsger Dijkstra. The goal is to simulate a scenario where a number of philosophers sit at a round table, alternating between eating, sleeping, and thinking. A fork is placed between each pair of adjacent philosophers, and a philosopher needs two forks to eat.

The core challenge is to prevent **deadlock** and **starvation** while ensuring no philosopher dies of hunger. This project introduces concurrent programming using **POSIX threads** (`pthread`) and **mutexes** for synchronization.

Key constraints:
- Each philosopher is a thread
- Each fork is protected by a mutex
- A monitor thread watches for death or meal completion
- No data races allowed

---

## Instructions

### Compilation

```bash
make
```

### Execution

```bash
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```

### Arguments

| Argument | Description |
|---|---|
| `number_of_philosophers` | Number of philosophers (and forks) |
| `time_to_die` | Time in ms before a philosopher dies without eating |
| `time_to_eat` | Time in ms a philosopher spends eating |
| `time_to_sleep` | Time in ms a philosopher spends sleeping |
| `number_of_times_each_philosopher_must_eat` | (Optional) Simulation stops when all philosophers have eaten this many times |

### Examples

```bash
# 5 philosophers, dies after 410ms, eats for 200ms, sleeps for 200ms
./philo 5 410 200 200

# Same but stops after each philosopher has eaten 3 times
./philo 5 410 200 200 3

# Edge case: 1 philosopher (can only pick up one fork, will die)
./philo 1 800 200 200
```

### Cleanup

```bash
make clean   # Remove object files
make fclean  # Remove object files and binary
make re      # Recompile from scratch
```

---

## Resources

### Documentation & References

- [POSIX Threads Programming – Lawrence Livermore National Laboratory](https://hpc-tutorials.llnl.gov/posix/) — comprehensive guide to pthreads, mutexes, and synchronization
- [Dining Philosophers Problem – Wikipedia](https://en.wikipedia.org/wiki/Dining_philosophers_problem) — problem statement and classic solutions
- [pthread_mutex_lock man page](https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3p.html)
- [gettimeofday man page](https://man7.org/linux/man-pages/man2/gettimeofday.2.html)

### AI Usage

AI (Claude) was used during this project for the following tasks:

- **Debugging**: Identifying pointer type mismatches (passing `t_data **` instead of `t_data *` to the monitor thread) and tracking down the root cause of segmentation faults
- **Code review**: Spotting issues such as duplicate function declarations in the header, unused variables, missing source files in the Makefile, and potential mutex locking order concerns
- **Refactoring feedback**: Verifying correctness after splitting files (e.g., extracting `philo_one.c`) and reorganizing initialization logic

All logic, architecture decisions, and final code were written and validated by the author.