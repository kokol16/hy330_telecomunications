# gr-cs330project

This repository is based on https://gitlab.com/surligas/gr-tutorial

GNU Radio OOT module containing flowgraphs and blocks for demonstrations 
and SDR learning.

Many of these examples and blocks are used in the series of presentations that 
can be found at https://gitlab.com/surligas/sdr-tutorial

## Build & Install

### Requirements
* [GNU Radio](https://wiki.gnuradio.org/index.php/InstallingGR) ( = 3.8)
* CMake ( > 3.1)
* Boost
* git
* swig

#### Debian/Ubuntu 
```bash
sudo apt install -y \
      libboost-dev \
      libboost-date-time-dev \
      libboost-filesystem-dev \
      libboost-program-options-dev \
      libboost-system-dev \
      libboost-thread-dev \
      libboost-regex-dev \
      libboost-test-dev \
      swig \
      cmake \
      build-essential \
      pkg-config \
      gnuradio-dev \
      libgmp-dev \
      liborc-0.4-0 \
      liborc-0.4-dev \
      liborc-0.4-dev-bin \
      git
```

#### openSUSE 
```bash
sudo zypper in -y \
      boost-devel \
      libboost_filesystem-devel \
      libboost_system-devel \
      libboost_thread-devel \
      libboost_program_options-devel \
      libboost_regex-devel \
      libboost_test-devel \
      python3 \
      python3-devel \
      swig \
      cmake \
      gcc-c++ \
      gcc \
      gnuradio \
      gnuradio-devel \
      gmp-devel \
      libmpir-devel \
      liborc-0_4-0 \
      orc \
      log4cpp-devel \
      git
```

### Installation

```bash
git clone https://gitlab.com/mraptakis/gr-cs330project.git
cd gr-cs330project
mkdir build
cd build
cmake ..
make -j $(nproc --all)
sudo make install
```

If this is the first time you are building the gr-cs330project module run
`sudo ldconfig`

#### Advanced
By default, the **gr-cs330project** module will use the default installation prefix.
This highly depends on the Linux distribution. You can use the `CMAKE_INSTALL_PREFIX`
variable to alter the default installation path.
E.g:

`cmake -DCMAKE_INSTALL_PREFIX=/usr ..`




