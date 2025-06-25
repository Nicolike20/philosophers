# philosophers

## 📚 About the Project

**philosophers** is a concurrency and synchronization project from the 42 coding school curriculum. It is a simulation of the classic **Dining Philosophers Problem**, designed to explore the challenges of multithreading, race conditions, and deadlock prevention in C.

The project demonstrates low-level handling of threads and mutexes, providing hands-on experience with concurrent programming and resource management.

---

## 🧩 Project Objective

Simulate a group of philosophers sitting at a table with forks between them. Each philosopher must:

- Think
- Pick up two forks (mutexes)
- Eat
- Sleep

The simulation must:

- Prevent race conditions and deadlocks
- Monitor philosophers for starvation (dying from not eating in time)
- Respect precise timing constraints

---

## ⚙️ Program Arguments

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Example:

```bash
./philo 5 800 200 200
```

- `number_of_philosophers`: Number of philosophers and forks
- `time_to_die`: Time (in ms) a philosopher can go without eating
- `time_to_eat`: Time (in ms) a philosopher spends eating
- `time_to_sleep`: Time (in ms) a philosopher spends sleeping
- `number_of_times_each_philosopher_must_eat` *(optional)*: Ends simulation when each philosopher has eaten this many times

---

## 🧠 Skills Demonstrated

- Multithreaded programming using `pthread`  
- Mutual exclusion with mutexes  
- Deadlock prevention and starvation handling  
- Accurate timing with `usleep` and time tracking  
- Clean and safe thread lifecycle management  
- Debugging and validating concurrency issues  
- Writing deterministic simulations with precise output

---

## 🛠️ How to Use

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/philosophers.git
   cd philosophers
   ```

2. Compile the project:
   ```bash
   make
   ```

3. Run the simulation:
   ```bash
   ./philo 5 800 200 200
   ```

4. (Optional) With eating limit:
   ```bash
   ./philo 5 800 200 200 5
   ```

---

## 🚀 Bonus Features

✅ Use of **processes** instead of threads (`philo_bonus`)  
✅ **Semaphores** for synchronization  
✅ **Accurate timestamping** and logging  
✅ Graceful termination and signal handling  
✅ Advanced deadlock avoidance strategies

---

## 📁 Project Status

✅ Completed – includes both mandatory and bonus versions, fully functional and tested for edge cases.

---

## 📌 Notes

- Output is synchronized and deterministic  
- All timing is measured in milliseconds  
- Complies strictly with 42's coding standards  
- Developed without any external concurrency libraries

---

## 📫 Contact

Feel free to reach out via [GitHub](https://github.com/Nicolike20) if you have any questions or want to connect.

[![forthebadge](https://forthebadge.com/images/featured/featured-built-with-love.svg)](https://forthebadge.com)
