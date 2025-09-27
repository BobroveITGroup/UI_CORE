## Connect with the Author

If you are interested in **articles about designing plugin systems** or want to see more of my projects, check out my [LinkedIn profile](https://www.linkedin.com/in/mmbcpp/) 👋  

[![LinkedIn](https://img.shields.io/badge/LinkedIn-Michael%20Bobrove-blue?logo=linkedin&logoColor=white)](https://www.linkedin.com/in/mmbcpp/)

---

# UI_CORE

**UI_CORE** is an experimental project designed to explore and test **plugin architecture** and dynamic UI concepts.  

The main goal of this project is to verify **hot-swap rendering** and prove that custom UI elements can be created and added easily **without modifying header files**.  

This project also serves as a proof-of-concept that a **plugin system can be convenient for development** and can scale to larger projects.

> ⚠️ Note: The code was written quickly. The focus was on algorithms, patterns, and architectural design of the plugin system rather than production-ready implementation.

---

## Features

- Plugin support (UI elements) via DLLs.  
- Dynamic loading and unloading of plugins.  
- EventBus for handling events.  
- Simple rendering via a custom renderer.  
- Experimental architecture focused on extensibility.

---

## Building the Project

1. **EventBus**  
   - Build EventBus as a static library (`.lib`).  
   - Required for all plugins, as it provides the core event system.

2. **Plugins**  
   - Build plugins as DLLs.  
   - Don’t forget to link `EventBus.lib`.

3. **Usage**  
   - Load plugins through the Renderer/UI API.  
   - Example usage can be found in the test/example folders.

---

## Architecture Overview

```mermaid
flowchart TD
    A[Application / Main] --> B[EventBus (singleton)]
    B --> C[IPlugin_Platform]
    C --> B
    B --> D[UI Plugin / Other Plugins]
    D --> B
    D --> E[Renderer]
    E --> F[Screen]

    style A fill:#f9f,stroke:#333,stroke-width:2px
    style B fill:#ff9,stroke:#333,stroke-width:2px
    style C fill:#9ff,stroke:#333,stroke-width:2px
    style D fill:#9f9,stroke:#333,stroke-width:2px
    style E fill:#f99,stroke:#333,stroke-width:2px
    style F fill:#ccc,stroke:#333,stroke-width:2px
```
