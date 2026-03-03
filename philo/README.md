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

https://note.com/syamashi/n/nd339d679bcd1

https://docs.google.com/presentation/d/12-lAykLu-RVACE1gI2aP-uEYZoOaeeFVYGh8W4ttTNw/edit?slide=id.gd4524b1be8_0_253#slide=id.gd4524b1be8_0_253

https://qiita.com/ryo_manba/items/e48faf2ba84f9e5d31c8

### AI Usage


All logic, architecture decisions, and final code were written and validated by the author.