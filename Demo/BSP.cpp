#include <fstream>
#include "BSP.hpp"

CBSP::CBSP()
{

}

CBSP::~CBSP()
{
	ReleaseLump(m_pNodes);
	ReleaseLump(m_pLeaves);
	ReleaseLump(m_pMarkSurfaces);
	ReleaseLump(m_pFaces);
	ReleaseLump(m_pClipNodes);
	ReleaseLump(m_pSurfEdges);
	ReleaseLump(m_pEdges);
	ReleaseLump(m_pVertices);
	ReleaseLump(m_pPlanes);
	ReleaseLump(m_pModels);
}

bool CBSP::LoadFromFile(const wchar_t *file_url)
{
	std::ifstream bsp;
	bsp.open(file_url, std::ios::in);

	if (!bsp.is_open())
	{
		std::wstring error_msg;
		error_msg = L"The ";
		error_msg += file_url;
		error_msg += L" couldn't be found";
		throw error_msg.c_str();
	}

	bsp.read(reinterpret_cast<char *>(&m_Header), sizeof(BSPHEADER));
	if (m_Header.nVersion != HL_BSP_VERSION)
	{
		std::wstring error_msg;
		error_msg = L"The ";
		error_msg += file_url;
		error_msg += L" was invalid";
		throw error_msg.c_str();
	}

	unsigned int nNodes, nLeaves, nMarkSurfaces, nFaces,
		nClipNodes, nSurfEdges, nEdges, nVertices, nPlanes,
		nModels;

	nNodes = AllocLump(LUMP_NODES, &m_pNodes);
	nLeaves = AllocLump(LUMP_LEAVES, &m_pLeaves);
	nMarkSurfaces = AllocLump(LUMP_MARKSURFACES, &m_pMarkSurfaces);
	nFaces = AllocLump(LUMP_FACES, &m_pFaces);
	nClipNodes = AllocLump(LUMP_CLIPNODES, &m_pClipNodes);
	nSurfEdges = AllocLump(LUMP_SURFEDGES, &m_pSurfEdges);
	nEdges = AllocLump(LUMP_EDGES, &m_pEdges);
	nVertices = AllocLump(LUMP_VERTICES, &m_pVertices);
	nPlanes = AllocLump(LUMP_PLANES, &m_pPlanes);
	nModels = AllocLump(LUMP_MODELS, &m_pModels);

	ReadLump(bsp, LUMP_NODES, m_pNodes, nNodes);
	ReadLump(bsp, LUMP_LEAVES, m_pLeaves, nLeaves);
	ReadLump(bsp, LUMP_MARKSURFACES, m_pMarkSurfaces, nMarkSurfaces);
	ReadLump(bsp, LUMP_FACES, m_pFaces, nFaces);
	ReadLump(bsp, LUMP_CLIPNODES, m_pClipNodes, nClipNodes);
	ReadLump(bsp, LUMP_SURFEDGES, m_pSurfEdges, nSurfEdges);
	ReadLump(bsp, LUMP_EDGES, m_pEdges, nEdges);
	ReadLump(bsp, LUMP_VERTICES, m_pVertices, nVertices);
	ReadLump(bsp, LUMP_PLANES, m_pPlanes, nPlanes);
	ReadLump(bsp, LUMP_MODELS, m_pModels, nModels);

	return true;
}

template<class T>
int CBSP::AllocLump(int lump_id, T **ppLump)
{
	int lump_count = m_Header.Lumps[lump_id].nLength / sizeof(T);
	*(ppLump) = new T[lump_count];
	return lump_count;
}

template<class T>
void CBSP::ReadLump(std::ifstream &bsp, int lump_id, T *pLump, int lump_count)
{
	bsp.seekg(m_Header.Lumps[lump_id].nOffset, std::ios::beg);
	bsp.read(reinterpret_cast<char *>(pLump), lump_count * sizeof(T));
}

template<class T>
void CBSP::ReleaseLump(T *&pLump)
{
	if (!pLump)
		return;

	delete []pLump;
	pLump = nullptr;
}
