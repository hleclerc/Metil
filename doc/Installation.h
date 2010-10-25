/*! \page Installation Installation

\section Requirements

    Basic requirements:
        - @ref CppCompiler "a C++ compiler and a correct IDE or editor(e.g. g++ with QtCreator...)"
    
    Optionnaly:
        - @subpage GitInstallation "Git", to download and manage patches (the "git-core" package under Debian-like systems)
        - lam-mpi, for parallel computations (the "liblam4-dev" package)
        - libhdf5, if you want to read or write hdf5 files (the "libhdf5-serial-dev" package)
        - libtiff, if you want to read or write .tiff images (the "libtiff4-dev" package)
        - libpng, if you want to read or write .png images (the "libpng12-dev" package)
        - libjpeg, if you want to read or write .jpg images (the "libjpeg62-dev" package)

\section GettingTheSources Getting the sources

    To get the latest production version with @subpage GitInstallation "Git", simply type:

    \code
git clone git://gitosis.lmt.ens-cachan.fr/met
    \endcode

    (if you do not have git on your machine, @subpage GitInstallation "this link" contains installation instructions)

    The test version is in the same host and is named <tt>met_test</tt>. The patches are send to the production repository only if they pass all the unit tests (located in the <tt>unit_tests</tt> directory of the sources).

    To facilitate compilation of your code or of the examples, you iirst need to generate the <tt>met_comp</tt> executable:

    \code
cd met # or where the sources are
make
sudo ln -s metil_comp /usr/bin # or add the source location in the PATH environment variable, or...
    \endcode

    You are no ready to start the @subpage Tutorials "tutorials".

\section DirectoryOrganisation Organisation of the sources

    Directories are organized in the following way:
    - src/*.[h,cpp]: the main source files
    - doc/*.h: documentation specific files
    - html_Level0: generated documentation for user level (using <tt>make documentation</tt>)
    - html_Level1: generated documentation for developpers (using <tt>make documentation</tt>)
    - unit_tests/*.cpp: gathers unit_tests
    - examples/*.cpp: contains a lot of (documented) examples

*/

