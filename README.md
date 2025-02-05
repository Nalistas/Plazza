# Plazza

## Description
Plazza is a multithreaded and multiprocess project designed to simulate a pizza restaurant's order management system. It efficiently handles incoming orders, distributes tasks among different kitchens, and ensures smooth communication between components using inter-process communication (IPC).

## Features
- Multi-threading for concurrent task execution.
- Multi-processing for scalable kitchen management.
- Inter-process communication (IPC) for order handling.
- Configurable parameters for restaurant simulation.
- Efficient task scheduling and synchronization.

## Installation
### Prerequisites
Make sure you have the following dependencies installed:
- g++ (C++ compiler supporting C++17 or later)
- Make
- POSIX-compliant system (Linux, macOS)

### Compilation
```sh
make
```
This will generate the executable `plazza`.

## Usage
Run the program with the following command:
```sh
./plazza <multiplier> <cooks_per_kitchen> <restock_time>
```
- `<multiplier>`: Time multiplier for pizza preparation.
- `<cooks_per_kitchen>`: Number of cooks per kitchen.
- `<restock_time>`: Time (in milliseconds) for ingredients to restock.

### Example
```sh
./plazza 2 5 1000
```
This runs the simulation with:
- A time multiplier of `2x`.
- `5` cooks per kitchen.
- Ingredients restocking every `1000ms`.

## How It Works
1. **Order Reception**: The main process receives pizza orders from the user.
2. **Kitchen Management**: Orders are distributed among different kitchens, each running as a separate process.
3. **Multithreading**: Each kitchen employs multiple cooks (threads) to prepare pizzas simultaneously.
4. **Synchronization & IPC**: Communication between the main process and kitchens is handled via IPC mechanisms.
5. **Restocking System**: Ingredients are automatically replenished after a fixed interval.

## Controls
- Enter commands to place pizza orders.
- Use `exit` to close the program.

## Contributors
- [Ambroise](https://github.com/Nalistas)
- [Satine](https://github.com/Satineee)

## License
This project is licensed under the MIT License.
