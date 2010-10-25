/*! \page FileFormats File formats (images, meshes, ...)

@section FileFormatsImages Images and arrays

    Supported I/O image and array files :
        - tiff (including 16 bits)
        - png
        - jpg
        - hdf5 (n dimensional)
        - raw data, if the user is able to define the type of the data and the size of the image
        - ascii data (matlab compatible)

@section FileFormatsMeshes Meshes

    Supported I/O mesh files :
        - gmsh2 (I)
        - pat (I)
        - stl (I)
        - unv (I/O)
        - inp (I)
        - gid (I)
        - geof (I)
        - hdf5 (I/O), with fields for position and connectivity with element names (e.g. "Triangle")

    To read/write abaqus dat files, you need the development files of Abaqus.

@section FileFormatsProblemDefinition Problem definition


@section FileFormatsCAD CAD


@section FileFormatsOutput Publication ready output

    The \ref VisualizationMetilTools "metil visualisation tools" allow to produce various image file format including pdf.
    
*/

