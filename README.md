# Low Level Devils

## Purpose
This repository serves as a shared workspace for small-scale, low-level engineering projects. It is intended both as a collaboration hub and as a showcase of personal and group projects across a wide range of technologies, including:

- Embedded systems (STM32, AVR, Arduino, ESP32, etc.)

- Firmware development in C/C++ and Rust

- Systems-level applications in C and C++

- Low-level tooling, utilities, and embedded experiments

- Miscellaneous low-level experiments and proofs of concept

This repository will also serve as a landing pad for those interested in low level learning but may not know where to start.

## Contributing
All contributors are welcome to submit projects as long as they follow the repository structure and collaboration workflow described below.

### Repository Structure

- Projects are organized under parent directories based on domain or platform.

### Directory Rules

- Each project must reside in its appropriate parent directory
(e.g., Embedded/STM32/MySTM32Project)

- One directory per project

### Images Folder
The images/ folder stores diagrams, schematics, block diagrams, serial logs, screenshots, and other assets referenced by project-level README files.

### Project-Level README Requirements

Every project must include its own README.md in the project’s root directory. The only exception to this is the initial projects I uploaded to keep the ball rolling. I'll add READMEs to them over time.

It is highly recommended the README should contain the following items:

1. **Project Description**

    - Explain what the project does, its purpose, and any notable design decisions.

2. **Required Components**

    - List all hardware, including (as applicable):

        - Microcontrollers (STM32 model, AVR chip, ESP32 variant, etc.)

        - Sensors, peripherals, and modules

        - Any external hardware dependencies

3. **Required Libraries or Toolchains**

- List all required libraries and toolchains you used from outside sources so others may recreate if desired

- Examples:

    - STM32Cube HAL or LL drivers

    - AVR-GCC version

    - Arduino core and third-party libraries

    - ESP-IDF release version

    - Rust crates and toolchain version

    - C/C++ standard libraries or build system requirements

4. **Build and Flash Instructions (Optional)**

- Provide platform-specific steps (e.g., CMake, Make, PlatformIO, CubeIDE).

- This is not required as users should know how to compile and flash code to their equipment already

### How to Contribute

Because the main branch is protected, no collaborator can push directly to main.
All contributions must be made via branches and pull requests.

Follow the workflow below for all changes:

0. **Prerequisite: Clone Repo**
- Clone the repo into a directory of your choice
```bash
git clone git@github.com:joshuawalker3/Low-Level-Devils.git
```

1. **Create a New Branch**

- Use a descriptive branch name, this is just an example:
```bash
git checkout -b feature/project-name
```

- Try to keep branch names descriptive but short

2. **Add Your Project Code**

- Do your based low level thing like the absolute animal you already are

- Stage the changes:

```bash
git add .
```

3. **Commit Your Work**
- It is recommended to add and commit changes frequently to allow easy experimentation and to return to the last known good point when you inevitably break something. Yes it will happen. A lot more than likely. This is low-level, if you can't handle it, go do web dev.
```bash
git commit -m "add led blinking task"
```

4. **Push the Branch to GitHub**
```bash
git push -u origin feature/project-name
```

5. **Create a Pull Request (PR)**

After pushing, visit the repository on GitHub.
GitHub will prompt you to create a PR from your branch.

Submit the PR.

If there are merge conflicts, fix them. If you don't know what that means, rech out to me on discord.

The PR queue will be checked frequently but if your request has no comments and hasn't been merged with 3 working days, reach out.

### Contribution Guidelines Summary

Keep each project isolated within its own directory.

Include a complete project README.

Do not commit build artifacts or binaries.

Respect the branch workflow—no direct pushes to main.

Keep commits focused and descriptive.