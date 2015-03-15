#pragma once
#include <vector>
#include "bspinfo.hpp"

class CBSP
{
public:
	CBSP();
	~CBSP();

	bool LoadFromFile(const wchar_t *file_name);

private:
	template<class T> int AllocLump(int lump_id, T **ppLump);
	template<class T> void ReadLump(int lump_id, T *pLump, int lump_count);

	template<class T> void ReleaseLump(T *&pLump);

private:

	// ---BSP DATA---
	BSPHEADER m_Header;

	BSPNODE *m_pNodes;
	BSPLEAF *m_pLeaves;
	BSPMARKSURFACE *m_pMarkSurfaces;
	BSPFACE *m_pFaces;
	BSPCLIPNODE *m_pClipNodes;
	BSPSURFEDGE *m_pSurfEdges;
	BSPEDGE *m_pEdges;
	BSPVERTEX *m_pVertices;
	BSPPLANE *m_pPlanes;
	BSPMODEL *m_pModels;
};
