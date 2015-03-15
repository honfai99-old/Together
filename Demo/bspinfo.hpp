#pragma once

// ### Basis
struct VECTOR3D
{
	float x, y, z;
};

// ### Headers (lumps/keys)
#define LUMP_ENTITIES		0
#define LUMP_PLANES			1
#define LUMP_TEXTURES		2
#define LUMP_VERTICES		3
#define LUMP_VISIBILITY		4
#define LUMP_NODES			5
#define LUMP_TEXINFO		6
#define LUMP_FACES			7
#define LUMP_LIGHTING		8
#define LUMP_CLIPNODES		9
#define LUMP_LEAVES			10
#define LUMP_MARKSURFACES	11
#define LUMP_EDGES			12
#define LUMP_SURFEDGES		13
#define LUMP_MODELS			14
#define HEADER_LUMPS		15

struct BSPLUMP
{
	int nOffset;		// the file offset to data
	int nLength;		// the length of data
};

struct BSPHEADER
{
#define HL_BSP_VERSION (30)
	int nVersion;					// must be 30 for a valid HL BSP file
	BSPLUMP Lumps[HEADER_LUMPS];	// stores the directory of lumps
};

#define MAX_MAP_HULLS			4

#define MAX_MAP_MODELS			400
#define MAX_MAP_BRUSHES			4096
#define MAX_MAP_ENTITIES		1024
#define MAX_MAP_ENTSTRING		(128*1024)

#define MAX_MAP_PLANES			32767
#define MAX_MAP_NODES			32767
#define MAX_MAP_CLIPNODES		32767
#define MAX_MAP_LEAFS			8192
#define MAX_MAP_VERTS			65535
#define MAX_MAP_FACES			65535
#define MAX_MAP_MARKSURFACES	65535
#define MAX_MAP_TEXINFO			8192
#define MAX_MAP_EDGES			256000
#define MAX_MAP_SURFEDGES		512000
#define MAX_MAP_TEXTURES		512
#define MAX_MAP_MIPTEX			0x200000
#define MAX_MAP_LIGHTING		0x200000
#define MAX_MAP_VISIBILITY		0x200000

#define MAX_MAP_PORTALS			65536

// ### The lump of entities (LUMP_ENTITIES)

#define MAX_KEY					32
#define MAX_VALUE				1024

// ### The lump of planes (LUMP_PLANES)

#define PLANE_X 0     // planes are alaways perpendicular to given axes
#define PLANE_Y 1
#define PLANE_Z 2
#define PLANE_ANYX 3  // non-axial planes are snapped to the nearest
#define PLANE_ANYY 4
#define PLANE_ANYZ 5

struct BSPPLANE
{
	VECTOR3D vecNormal;						// the planes normal vector
	float fDist;							// plane equation is: vNormal * X = fDist (Hesse normal form) # (normal * point - distance = 0 )
	int nType;								// plane type, see #defines
};

// ### The lump of textures (LUMP_TEXTURES)

struct BSPTEXTUREHEADER
{
	unsigned int nMipTextures;					// number of BSPMIPTEX structures
};

typedef int BSPMIPTEXOFFSET;

#define MAXTEXTURENAME 16
#define MIPLEVELS 4

typedef struct _BSPMIPTEX
{
	char szName[MAXTEXTURENAME];				// the name of texture
	unsigned int nWidth, nHeight;				// extends of the texture
	unsigned int nOffsets[MIPLEVELS];			// the offsets to its mipmaps BSPMIPTEX;
} BSPMIPTEX;

// ### The lump of vertics (LUMP_VERTICES)

typedef VECTOR3D BSPVERTEX;

// ### The lump of VIS (LUMP_VISIBILITY)

// ### The lump of nodes (LUMP_NODES)

struct BSPNODE
{
	unsigned int iPlane;				// index into Planes lump
	short iChildren[2];					// if > 0, then indices into Nodes // otherwise bitwise inverse indices into Leafs
	short nMins[3], nMaxs[3];			// defines bounding box
	unsigned short firstFace, nFaces;	// index and count into Faces
};

// ### The lump of textures info. (LUMP_TEXINFO)

struct BSPTEXTUREINFO
{
	VECTOR3D vS;
	float fSShift;					// texture shift in s direction
	VECTOR3D vT;
	float fTShift;					// texture shift in t direction
	unsigned int iMiptex;			// index into textures array
	unsigned int nFlags;			// texture flags, seem to always be 0
};

// ### The lump of faces (LUMP_FACES)

struct BSPFACE
{
	unsigned short iPlane;				// plane the face is parallel to
	unsigned short nPlaneSide;			// set if different normals orientation
	unsigned int iFirstEdge;			// index of the first surfedge
	unsigned short nEdges;				// number of consecutive surfedges
	unsigned short iTextureInfo;		// index of the texture info structure
	unsigned char nStyles[4];			// specify lighting styles
	unsigned int nLightmapOffset;		// offsets into the raw lightmap data
};

// ### The lump of lightmap (LUMP_LIGHTING)

// ### The lump of clipnodes (LUMP_CLIPNODES)

struct BSPCLIPNODE
{
	int iPlane;       // Index into planes
	short iChildren[2]; // negative numbers are contents
};

// ### The lump of leaves (LUMP_LEAVES)

#define CONTENTS_EMPTY        -1
#define CONTENTS_SOLID        -2
#define CONTENTS_WATER        -3
#define CONTENTS_SLIME        -4
#define CONTENTS_LAVA         -5
#define CONTENTS_SKY          -6
#define CONTENTS_ORIGIN       -7
#define CONTENTS_CLIP         -8
#define CONTENTS_CURRENT_0    -9
#define CONTENTS_CURRENT_90   -10
#define CONTENTS_CURRENT_180  -11
#define CONTENTS_CURRENT_270  -12
#define CONTENTS_CURRENT_UP   -13
#define CONTENTS_CURRENT_DOWN -14
#define CONTENTS_TRANSLUCENT  -15

struct BSPLEAF
{
	int nContents;											// contents enumeration
	int nVisOffset;											// offset into the visibility lump
	short nMins[3], nMaxs[3];								// defines bounding box
	unsigned short iFirstMarkSurface, nMarkSurfaces;		// index and count into marksurfaces array
	unsigned char nAmbientLevels[4];						// ambient sound levels
};

// ### The lump of marksurfaces (LUMP_MARKSURFACES)

typedef unsigned short BSPMARKSURFACE;

// ### The lump of edges (LUMP_EDGES)

struct BSPEDGE
{
	unsigned short iVertex[2]; // indices into vertex array
};

// ### The lump of surfedges (LUMP_SURFEDGES)

typedef int BSPSURFEDGE;

// ### The lump of models (LUMP_MODELS)

#define MAX_MAP_HULLS 4

struct BSPMODEL
{
	float nMins[3], nMaxs[3];			// defines bounding box
	VECTOR3D vOrigin;					// coordinates to move the // coordinate system
	int iHeadnodes[MAX_MAP_HULLS];		// index into nodes array
	int nVisLeafs;						// ???
	int iFirstFace, nFaces;				// index and count into faces
};
