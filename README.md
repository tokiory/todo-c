# Todo-C

A simple, lightweight command-line todo application written in C with custom data structures and file-based storage.

## Features

- ✅ Create, read, update, and delete tasks
- ✅ Mark tasks as completed
- ✅ Persistent file-based storage
- ✅ UUID-based task identification
- ✅ Custom hashmap and vector implementations
- ✅ Multiple command aliases for convenience

## Architecture

The application is built with a modular architecture:

- **Custom Data Structures**: Implementation of hashmap and vector from scratch
- **Storage Layer**: File-based persistence with tab-separated values
- **Command Processing**: Flexible command parsing with multiple aliases
- **Adapter Pattern**: Clean separation between storage and business logic

## Building

### Prerequisites

- CMake 3.16 or higher
- C99 compatible compiler (GCC, Clang)
- UUID library (`libuuid-dev` on Ubuntu/Debian, `uuid-dev` on other systems)

### Build Instructions

```bash
# Clone the repository
git clone <repository-url>
cd todo-c

# Create build directory
mkdir build
cd build

# Configure and build
cmake ..
make

# Run the application
./todo-c
```

## Usage

### Basic Commands

```bash
# Show help
./todo-c help
./todo-c h
./todo-c -h
./todo-c --help

# Add a new task
./todo-c add "Buy groceries"
./todo-c a "Buy groceries"
./todo-c -a "Buy groceries"
./todo-c --add "Buy groceries"

# List all tasks
./todo-c ls
./todo-c --list
./todo-c -l

# Mark a task as done
./todo-c done <task-id>
./todo-c do <task-id>
./todo-c --done <task-id>

# Update a task
./todo-c upd <task-id> "New task title"
./todo-c u <task-id> "New task title"
./todo-c --update <task-id> "New task title"
./todo-c -u <task-id> "New task title"

# Delete a task
./todo-c del <task-id>
./todo-c d <task-id>
./todo-c -d <task-id>
./todo-c --del <task-id>
```

## Data Storage

Tasks are stored in a tab-separated file (`storage.txt`) with the following format:
```
<task-id>\t<task-title>\t<is-done>
```

Where:
- `task-id`: UUID string
- `task-title`: Task description
- `is-done`: "1" for completed, "0" for pending

## Project Structure

```
todo-c/
├── src/
│   ├── main.c           # Entry point and command dispatch
│   ├── command.c        # Command parsing and help
│   ├── todo.c           # Core todo logic
│   ├── storage.c        # File I/O operations
│   ├── adapter.c        # Storage-Todo conversion
│   └── lib/
│       ├── hashmap.c    # Custom hashmap implementation
│       └── vector.c     # Dynamic array implementation
├── include/
│   ├── command.h
│   ├── todo.h
│   ├── storage.h
│   ├── adapter.h
│   └── lib/
│       ├── hashmap.h
│       └── vector.h
├── CMakeLists.txt       # Build configuration
└── README.md
```

## Implementation Details

### Custom Data Structures

- **Hashmap**: Uses FNV1A hash function with linked list collision resolution
- **Vector**: Dynamic array with automatic resizing (doubles capacity when full)

### Error Handling

- Graceful handling of missing files (creates new storage)
- Input validation for commands
- Proper error messages for invalid operations

## Contributing

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Ensure all memory leaks are fixed
5. Test thoroughly
6. Submit a pull request

## Dependencies

- **libuuid**: For generating unique task identifiers
- **CMake**: Build system
- **Standard C Library**: Core functionality

## Development Notes

- Uses C99 standard
- Debug builds include `-g -O0` flags
- Compile commands are exported for IDE integration
- Custom implementations prioritize learning over performance
