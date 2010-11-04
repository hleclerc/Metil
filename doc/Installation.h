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
git clone git://gitosis.lmt.ens-cachan.fr/Metil
    \endcode

    The test version is in the same host and is named <tt>MetilTest</tt>. The patches are send to the production repository only if they pass all the unit tests (located in the <tt>unit_tests</tt> directory of the sources).


\section DirectoryOrganisation Organisation of the sources

    Directories are organized in the following way:
    - Metil/src/*.[h,cpp]: the main source files
    - Metil/doc/*.h: documentation specific files
    - Metil/metil_comp/*.[h,cpp]: metil_comp sources
    - Metil/unit_tests/*.cpp: gathers unit_tests
    - Metil/tests/*.cpp: gathers ??
    - Metil/examples/*.cpp: contains a lot of (documented) examples
    - Metil/html: generated documentation (using <tt>make documentation</tt>)

\section PreliminaryBuilding Preliminary building

    Go to Metil directory:
    \code
cd Metil 
    \endcode

    To facilitate compilation of your code or of the examples, you first need to generate the <tt>metil_comp</tt> executable:

    \code
make # build metil_comp
    \endcode

    The executable <tt>Metil/metil_comp/metil_comp</tt> should be accessible from any location. For instance you can put a symbolic link in a directory belonging to your <tt>${PATH}</tt>. The following command automatically make this link (by default in <tt>/usr/bin</tt>).

    \code
sudo make install  
    \endcode

    You are now ready to start the @subpage Tutorials "tutorials".

    If you wish to generate this documentation, simply execute the following command 
    \code
make documentation
    \endcode

    The documentation will be created in <tt>Metil/html</tt>. Use your favorite browser to read file <tt>Metil/html/index.html</tt>
*/

