# HADES

**HADES** is a hardware-accelerated framework for bit-true fixed-point simulation and bit-width optimization of computational applications on FPGAs.

The framework evaluates a configurable fixed-point implementation against a high-precision reference implementation and searches for reduced integer and fractional widths while maintaining a user-defined numerical error constraint. The main HLS implementation is organized as a reusable framework that can be adapted to different applications through a defined application interface.

The repository contains:

- a reusable **Vitis HLS framework**;
- configurable arithmetic building blocks;
- a **dynamic-range-based integer-width estimation** stage;
- a **fractional-width optimization** stage;
- a template for integrating new applications;
- HLS and software implementations of several example applications;
- final optimized and unoptimized implementations for comparison;
- an earlier RTL implementation and MATLAB support files.

---

## Repository structure

```text
HADES/
├── FPS_HLS/
│   ├── Blank_Framework/
│   ├── Library/
│   └── Benchmarks/
│       ├── FIR_10/
│       ├── FIR_30/
│       ├── IIR/
│       ├── LMS/
│       └── Polynomial/
│
└── FPS_RTL/
    ├── MATLAB/
    └── RTL/
```

### `FPS_HLS/Blank_Framework/`

A generic template for integrating a new application with HADES.

```text
Blank_Framework/
├── Application.cpp
├── Application.h
├── DR.cpp
├── DR.h
├── FracOpt.cpp
├── FracOpt.h
├── GlobalParameters.h
├── TIW.cpp
├── TIW.h
├── WCAdder.cpp
├── WCAdder.h
├── WCMultiplier.cpp
├── WCMultiplier.h
├── WidthAdapter.cpp
├── WidthAdapter.h
├── WidthOptimizer.cpp
└── WidthOptimizer.h
```

The Blank Framework is intended to be adapted by the user and is therefore a template rather than a ready-to-run benchmark.

The main application-specific integration points are documented directly in the source files.

### `FPS_HLS/Library/`

Reusable configurable arithmetic components:

- `WCAdder`
- `WCMultiplier`
- `WidthAdapter`

These components can be used independently when implementing an application around the HADES framework.

### `FPS_HLS/Benchmarks/`

Example applications used with the framework:

| Benchmark | Application type |
|---|---|
| `FIR_10` | 10-tap finite impulse response filter |
| `FIR_30` | 30-tap finite impulse response filter |
| `IIR` | Infinite impulse response filter |
| `LMS` | Least mean squares adaptive filter |
| `Polynomial` | Polynomial evaluation |

Each benchmark generally contains:

```text
Benchmark/
├── HLS_Code/
├── SW_Code/
└── Final_Implementations/
```

`HLS_Code` contains the HLS implementation of the simulation and optimization framework for the benchmark.

`SW_Code` contains a software version used for software-based execution and comparison.

`Final_Implementations` contains optimized and unoptimized fixed-point implementations together with the corresponding test/configuration files.

### `FPS_RTL/`

Contains the earlier RTL implementation of the framework and associated MATLAB material.

```text
FPS_RTL/
├── MATLAB/
│   └── FIR.m
└── RTL/
    ├── BasicAddSub.vhd
    ├── BasicMult.vhd
    ├── FIR_TOP.vhd
    ├── parameters.vhd
    ├── WC_AddSub.vhd
    ├── WC_Mult.vhd
    └── WidthAdapter.vhd
```

The RTL implementation is provided as a reference implementation and is separate from the HLS framework.

---

# Framework overview

HADES separates the application datapath from the hardware used to evaluate and optimize its fixed-point representation.

At a high level, the process is:

```text
                    Application
                         │
                         ▼
                ┌─────────────────┐
                │  Golden / DUT   │
                │    instances    │
                └────────┬────────┘
                         │
                         ▼
              Width-configurable
                 arithmetic
                         │
             ┌───────────┴───────────┐
             │                       │
             ▼                       ▼
     Dynamic-Range (DR)       Fractional-Width
        estimation             Optimization
             │                       │
             └───────────┬───────────┘
                         ▼
                  Optimized widths
                    (CIW / CFW)
```

The Golden instance provides the reference behavior, while the DUT (device under test) uses runtime-configurable integer and fractional widths.

The framework repeatedly evaluates these two instances to determine whether reduced widths satisfy the configured numerical error requirement.

---

# Main framework components

## `Application`

`Application.cpp` and `Application.h` define the application integration interface.

The user supplies the actual application datapath and connects it to the configurable arithmetic components.

The application implementation is responsible for:

1. defining the application datapath;
2. identifying the intermediate variables whose widths are to be optimized;
3. using the configurable arithmetic blocks where appropriate;
4. providing the application output;
5. handling application-specific state or memory.

The framework supports two application instances:

- **Golden instance** — reference implementation using the configured maximum/reference widths;
- **DUT instance** — implementation using the candidate integer and fractional widths being evaluated.

The Blank Framework contains comments at the relevant integration points.

---

## `TIW`

`TIW` provides the interface between the framework and the application.

It evaluates the application using both the Golden and DUT configurations for the same input.

Conceptually:

```text
Input
  │
  ├──────────────► Golden Application ─────► Golden output
  │
  └──────────────► DUT Application ────────► DUT output
```

This allows the framework to compare the candidate fixed-point implementation with the reference implementation.

Application-specific state or memory elements are integrated at this level when required. For example, recursive or adaptive applications may require separate state for the Golden and DUT instances.

---

## `WCAdder`

`WCAdder` implements width-configurable addition/subtraction.

The input widths are supplied at runtime, allowing different width configurations to be evaluated without creating a separate application implementation for every candidate width combination.

---

## `WCMultiplier`

`WCMultiplier` implements width-configurable multiplication.

As with `WCAdder`, the operand widths are supplied through the framework configuration so that candidate fixed-point representations can be evaluated during optimization.

---

## `WidthAdapter`

`WidthAdapter` handles the conversion between the global datapath representation and the effective integer/fractional widths used by the configurable arithmetic operations.

The global datapath provides the maximum/reference representation, while the effective widths determine the candidate fixed-point representation evaluated by the DUT.

---

# Width optimization

The optimization is divided into two principal stages.

## 1. Dynamic-range estimation

`DR.cpp` determines the required integer widths of the intermediate variables.

The framework evaluates the application and observes the intermediate values. These values are then used to determine suitable integer widths.

The framework supports the configured dynamic-range calculation modes through `DRMode`.

The resulting integer widths are stored in:

```cpp
FinalCIW
```

where each entry corresponds to an intermediate variable.

---

## 2. Fractional-width optimization

`FracOpt.cpp` determines the fractional widths while keeping the integer widths obtained from the dynamic-range stage.

The optimization uses the Golden and DUT outputs to evaluate the numerical error associated with candidate width configurations.

The configured error threshold determines whether a candidate configuration is accepted.

The resulting fractional widths are stored in:

```cpp
FinalCFW
```

The fractional-width optimization consists of:

### Coarse optimization

A global fractional-width search establishes an initial fractional-width configuration.

### Fine optimization stage I

Individual fractional widths are reduced and evaluated to identify variables where fractional-width reductions have limited effect on the resulting error.

### Fine optimization stage II

Fractional bits are redistributed between intermediate variables according to their sensitivity.

The implementation evaluates candidate configurations using the configured error calculation before accepting a redistribution.

---

# `WidthOptimizer`

`WidthOptimizer.cpp` is the top-level HLS module coordinating the optimization process.

Its main sequence is:

```text
1. Dynamic-range estimation
          │
          ▼
   Integer widths (CIW)
          │
          ▼
2. Fractional-width optimization
          │
          ▼
   Fractional widths (CFW)
```

The final integer and fractional widths are returned through:

```cpp
width_t *FinalCIW
width_t *FinalCFW
```

The module also provides the cycle count used by the framework's execution-time measurements.

`WidthOptimizer` should not be confused with an application testbench. It is the top-level framework module that executes the width-optimization procedure.

---

# Configuration

The main framework-wide configuration is located in:

```text
GlobalParameters.h
```

Important parameters include:

```cpp
GI
GF
IVNum
InArraySize
InArraySizeR
DRMode
ErrMethod
ErrorThreshold
SCALING_FACTOR
```

## Global widths

`GI` and `GF` define the global integer and fractional widths used by the framework's maximum/reference datapath.

## `IVNum`

`IVNum` specifies the number of intermediate variables whose widths are considered by the optimization.

This value is application-dependent and must be set by the user.

## `InArraySize`

`InArraySize` specifies the number of input samples/vectors processed during one simulation and optimization procedure.

This value must be configured for the target application and dataset.

## `InArraySizeR`

`InArraySizeR` is the reciprocal of `InArraySize` and is used in the error calculation.

## `DRMode`

Selects the dynamic-range estimation mode.

## `ErrMethod`

Selects the configured numerical error calculation method.

## `ErrorThreshold`

Defines the maximum permitted error for the optimization procedure.

## `SCALING_FACTOR`

Defines the number of standard deviations used by the statistical dynamic-range estimation mode.

---

# Adding a new application

The recommended starting point for a new application is:

```text
FPS_HLS/Blank_Framework/
```

A typical integration process is:

### 1. Copy the Blank Framework

Create an application-specific directory under:

```text
FPS_HLS/Benchmarks/
```

### 2. Define the application parameters

Modify:

```text
GlobalParameters.h
```

and provide at least:

- `IVNum`
- `InArraySize`
- `InArraySizeR`
- application-specific parameters
- the input dataset used by the simulation

### 3. Implement `Application`

Replace the template implementation in:

```text
Application.cpp
Application.h
```

with the target application's datapath.

Identify all intermediate variables that should participate in width optimization.

### 4. Integrate configurable arithmetic

Replace arithmetic operations whose widths should be optimized with the corresponding configurable operators:

```text
WCAdder
WCMultiplier
```

Use `WidthAdapter` where required by the datapath representation.

### 5. Integrate application state

For applications containing state or memory, such as recursive or adaptive algorithms, provide separate state for the Golden and DUT instances.

The relevant integration point is documented in `TIW.cpp`.

### 6. Configure the simulation dataset

Provide the input data expected by the application and set:

```cpp
InArraySize
```

accordingly.

### 7. Run the width optimization

The top-level module is:

```text
WidthOptimizer
```

The resulting arrays contain the optimized integer and fractional widths:

```text
FinalCIW
FinalCFW
```

### 8. Use the resulting widths

The optimized widths can then be used to construct a fixed-width implementation of the application.

The benchmark directories in this repository provide examples of this final implementation stage.

---

# Benchmark organization

The included benchmarks demonstrate the framework across different classes of computational applications.

## FIR

The FIR examples contain:

- 10-tap FIR;
- 30-tap FIR.

These demonstrate feed-forward filter datapaths containing configurable multipliers and adders.

## IIR

The IIR benchmark demonstrates the use of the framework with a recursive datapath and application state.

## LMS

The LMS benchmark demonstrates the framework with an adaptive algorithm and state-dependent processing.

## Polynomial

The Polynomial benchmark demonstrates width optimization for arithmetic-intensive nonlinear computation.

The benchmarks are provided both as HLS framework implementations and software implementations, together with final optimized/unoptimized fixed-point implementations where available.

---

# HLS and software implementations

The repository contains two implementations of the HLS-oriented framework for the benchmarks:

```text
HLS_Code/
SW_Code/
```

The HLS version contains the hardware-oriented implementation intended for synthesis and hardware execution.

The software version contains corresponding C++ implementations that can be compiled and executed in a conventional software development environment. These are useful for algorithm-level evaluation and comparison without synthesizing the HLS design.

The HLS directories contain the framework modules together with the application-specific implementation and testbench.

---

# Final implementations

The benchmark directories contain:

```text
Final_Implementations/
├── <Application>_Opt/
└── <Application>_Unopt/
```

where present.

The optimized implementations use the widths obtained through the HADES optimization procedure.

The unoptimized implementations provide a corresponding fixed-point implementation using the non-optimized width configuration.

The final implementation directories also contain input data and width/configuration files used by the corresponding examples.

---

# Error evaluation

The framework compares the Golden and DUT outputs for the configured simulation dataset.

The error calculation is implemented in `FracOpt.cpp` and is controlled through the framework parameters.

The repository's framework supports the error methods represented by `ErrMethod`. The exact metric used for a particular benchmark is determined by that benchmark's configuration.

The optimization accepts a candidate width configuration when its calculated error satisfies the configured `ErrorThreshold`.

---

# Reproducibility

The repository is intended to provide the source material required to reproduce the framework evaluations.

For each benchmark, the repository includes combinations of:

- application source code;
- framework source code;
- configurable arithmetic components;
- input data;
- width configuration files;
- HLS testbenches;
- software implementations;
- optimized fixed-point implementations;
- unoptimized fixed-point implementations.

The `Blank_Framework` directory additionally provides the generic integration structure for extending HADES to other applications.

There is no single repository-wide build script because the HLS and software examples are organized as application-specific source projects.

---

# Hardware description

The repository also contains an earlier RTL implementation under:

```text
FPS_RTL/RTL/
```

This implementation contains:

- configurable add/subtract hardware;
- configurable multiplier hardware;
- width adaptation;
- the FIR top-level design;
- global RTL parameters.

The RTL implementation is retained separately from the HLS framework.

---

# Requirements

The HLS source is written in C++ for high-level synthesis and uses arbitrary-precision fixed-point/integer types such as:

```cpp
ap_fixed
ap_int
```

provided by the AMD/Xilinx HLS environment.

The benchmark HLS code should therefore be used within a compatible Vitis HLS environment.

The software versions are standard C++ implementations and can be used independently of HLS for software-side evaluation.

The repository itself does not contain a universal build system; individual benchmark directories contain their respective source files and testbenches.

---

# Important design concepts

## Golden and DUT datapaths

The framework evaluates two instances of the application:

**Golden**

- uses the reference/global widths;
- provides the reference output;
- supplies intermediate values for dynamic-range analysis.

**DUT**

- uses candidate integer/fractional widths;
- represents the optimized fixed-point implementation;
- is compared against the Golden output.

This separation allows width configurations to be evaluated without changing the application source for every candidate configuration.

## Runtime-configurable widths

The configurable arithmetic components allow the effective widths of intermediate operations to be changed during the optimization procedure.

The framework therefore evaluates many candidate width configurations using the same hardware-oriented application structure.

## Separation of application and optimization framework

The optimization framework is separated from the application datapath.

A new application primarily requires:

1. application-specific parameters;
2. an application implementation;
3. identification of intermediate variables;
4. integration of application state where necessary;
5. an input dataset.

The dynamic-range and fractional-width optimization modules remain part of the common framework.

---

# Limitations

The configurable arithmetic library included in the framework currently focuses on the arithmetic operations implemented by:

- `WCAdder`;
- `WCMultiplier`.

Applications requiring other specialized operations may require additional configurable hardware blocks or application-specific extensions.

The provided width-optimization methodology is designed around the fixed-point simulation and error-evaluation flow implemented in HADES. Different application classes or numerical representations may require modifications to the optimization methodology.

The repository should therefore be viewed as both:

- a reusable hardware framework; and
- a reference implementation of the presented width-optimization approach.

---

# Repository status

The repository contains the implementation and benchmark source associated with the HADES framework, including both the reusable framework template and the benchmark-specific implementations.

The `Blank_Framework` is the recommended starting point for extending HADES to a new application.

---

# Citation

If you use HADES or the implementations provided in this repository in academic work, please cite the associated HADES publication:

> **K. Shahin, C. Herglotz, and M. Hübner, "HADES: A Hardware-Accelerated FPGA Framework for Bit-True Fixed-Point Simulation and Bit-Width Optimization."**

Please use the final bibliographic information of the associated publication when citing the work.

---

# Authors

**Keyvan Shahin**  
Brandenburg University of Technology Cottbus-Senftenberg (BTU)

The framework was developed as part of research on hardware-accelerated fixed-point simulation and bit-width optimization for FPGA-based implementations.

