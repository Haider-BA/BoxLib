
#include "hg_multi.H"

#ifdef BL_FORT_USE_UNDERSCORE
#  define   FORT_HGFRES     hgfres_
#  define   FORT_HGFRES_TERRAIN     hgfres_terrain_
#  define   FORT_HGFRES_FULL_STENCIL     hgfres_full_stencil_
#  define   FORT_HGERES     hgeres_
#  define   FORT_HGERES_TERRAIN     hgeres_terrain_
#  define   FORT_HGCRES     hgcres_
#  define   FORT_HGCRES_TERRAIN     hgcres_terrain_
#  define   FORT_HGORES     hgores_full_stencil_
#  define   FORT_HGIRES     hgires_full_stencil_
#  define   FORT_HGDRES     hgdres_full_stencil_
#else
#  define   FORT_HGFRES     HGFRES
#  define   FORT_HGFRES_TERRAIN     HGFRES_TERRAIN
#  define   FORT_HGFRES_FULL_STENCIL     HGFRES_FULL_STENCIL
#  define   FORT_HGERES     HGERES
#  define   FORT_HGERES_TERRAIN     HGERES_TERRAIN
#  define   FORT_HGCRES     HGCRES
#  define   FORT_HGCRES_TERRAIN     HGCRES_TERRAIN
#  define   FORT_HGORES     HGORES_FULL_STENCIL
#  define   FORT_HGIRES     HGIRES_FULL_STENCIL
#  define   FORT_HGDRES     HGDRES_FULL_STENCIL
#endif

extern "C" 
{
    
#if (BL_SPACEDIM == 1)
#error not relevant
#elif (BL_SPACEDIM == 2)
    void FORT_HGFRES_TERRAIN(Real*, intS, Real*, intS, Real*, intS, Real*, intS, Real*, intS, Real*, intS, intS, intRS, const int*, const int*);
    void FORT_HGCRES_TERRAIN(Real*, intS, Real*, intS, Real*, intS, Real*, intS, Real*, intS, Real*, intS, intS, intRS, const int*);
    void FORT_HGIRES(Real*, intS, Real*, intS, Real*, intS, Real*, intS, Real*, intS, Real*, intS, intS, CRealPS, intRS, const int *, const int *, const int* );
    void FORT_HGDRES(Real*, intS, Real*, intS, Real*, intS, Real*, intS, Real*, intS, Real*, intS, intS, CRealPS, intRS, const int *, const int* );
    void FORT_HGCRES(Real*, intS, Real*, intS, Real*, intS, Real*, intS, Real*, intS, Real*, intS, intS, CRealPS, intRS, const int*);
    void FORT_HGFRES(Real*, intS, Real*, intS, Real*, intS, Real*, intS, Real*, intS, Real*, intS, intS, CRealPS, intRS, const int*, const int*);
    void FORT_HGFRES_FULL_STENCIL(Real*, intS, Real*, intS, Real*, intS, Real*, intS, Real*, intS, Real*, intS, intS, CRealPS, intRS, const int*, const int*, const int*, const int*);
    void FORT_HGORES(Real*, intS, Real*, intS, Real*, intS, Real*, intS, Real*, intS, Real*, intS, intS, CRealPS, intRS, const int *, const int *, const int* );
#elif (BL_SPACEDIM == 3)
    void FORT_HGFRES_TERRAIN(Real*, intS, Real*, intS, Real*, intS, Real*, intS, Real*, intS, Real*, intS, intS, intRS, const int*, const int*);
    void FORT_HGERES_TERRAIN(Real*, intS, Real*, intS, Real*, intS, Real*, intS, Real*, intS, Real*, intS, intS, intRS, const int*, const int*);
    void FORT_HGCRES_TERRAIN(Real*, intS, Real*, intS, Real*, intS, Real*, intS, Real*, intS, Real*, intS, intS, intRS, const int*);
    void FORT_HGFRES(Real*, intS, Real*, intS, Real*, intS, Real*, intS, Real*, intS, Real*, intS, intS, CRealPS, intRS, const int*, const int*);
    void FORT_HGERES(Real*, intS, Real*, intS, Real*, intS, Real*, intS, Real*, intS, Real*, intS, intS, CRealPS, intRS, const int*, const int*);
    void FORT_HGCRES(Real*, intS, Real*, intS, Real*, intS, Real*, intS, Real*, intS, Real*, intS, intS, CRealPS, intRS, const int*);
#endif
}

void holy_grail_amr_multigrid::alloc_sync_caches()
{
    if (lev_min < lev_max) 
    {
	fres_fbox  = new Box*[lev_max+1];
	fres_cbox  = new Box*[lev_max+1];
	fres_creg  = new Box*[lev_max+1];
	fres_sfbox = new Box*[lev_max+1];
	fres_scbox = new Box*[lev_max+1];
	fres_sc = new PArray<FArrayBox>[lev_max+1];
	fres_dc = new PArray<FArrayBox>[lev_max+1];
	fres_flag = new int*[lev_max+1];
#if (BL_SPACEDIM == 3)
	eres_fbox  = new Box*[lev_max+1];
	eres_cbox  = new Box*[lev_max+1];
	eres_creg  = new Box*[lev_max+1];
	eres_sfbox = new Box*[lev_max+1];
	eres_scbox = new Box*[lev_max+1];
	eres_sf = new PArray<FArrayBox>[lev_max+1];
	eres_sc = new PArray<FArrayBox>[lev_max+1];
	eres_df = new PArray<FArrayBox>[lev_max+1];
	eres_dc = new PArray<FArrayBox>[lev_max+1];
	eres_flag = new int*[lev_max+1];
#endif
	cres_fbox  = new Box*[lev_max+1];
	cres_cbox  = new Box*[lev_max+1];
	cres_creg  = new Box*[lev_max+1];
	cres_sfbox = new Box*[lev_max+1];
	cres_scbox = new Box*[lev_max+1];
	cres_sf = new PArray<FArrayBox>[lev_max+1];
	cres_sc = new PArray<FArrayBox>[lev_max+1];
	cres_df = new PArray<FArrayBox>[lev_max+1];
	cres_dc = new PArray<FArrayBox>[lev_max+1];
	cres_flag = new int*[lev_max+1];
    }
    
    for (int lev = lev_min + 1; lev <= lev_max; lev++) 
    {
	int mglev = ml_index[lev];
	fres_fbox[lev]  = new Box[lev_interface[mglev].nfaces()];
	fres_cbox[lev]  = new Box[lev_interface[mglev].nfaces()];
	fres_creg[lev]  = new Box[lev_interface[mglev].nfaces()];
	fres_sfbox[lev] = new Box[lev_interface[mglev].nfaces()];
	fres_scbox[lev] = new Box[lev_interface[mglev].nfaces()];
	fres_sc[lev].resize(lev_interface[mglev].nfaces());
	fres_dc[lev].resize(lev_interface[mglev].nfaces());
	fres_flag[lev] = new int[lev_interface[mglev].nfaces()];
#if (BL_SPACEDIM == 3)
	eres_fbox[lev]  = new Box[lev_interface[mglev].nedges()];
	eres_cbox[lev]  = new Box[lev_interface[mglev].nedges()];
	eres_creg[lev]  = new Box[lev_interface[mglev].nedges()];
	eres_sfbox[lev] = new Box[lev_interface[mglev].nedges()];
	eres_scbox[lev] = new Box[lev_interface[mglev].nedges()];
	eres_sf[lev].resize(lev_interface[mglev].nedges());
	eres_sc[lev].resize(lev_interface[mglev].nedges());
	eres_df[lev].resize(lev_interface[mglev].nedges());
	eres_dc[lev].resize(lev_interface[mglev].nedges());
	eres_flag[lev] = new int[lev_interface[mglev].nedges()];
#endif
	cres_fbox[lev]  = new Box[lev_interface[mglev].ncorners()];
	cres_cbox[lev]  = new Box[lev_interface[mglev].ncorners()];
	cres_creg[lev]  = new Box[lev_interface[mglev].ncorners()];
	cres_sfbox[lev] = new Box[lev_interface[mglev].ncorners()];
	cres_scbox[lev] = new Box[lev_interface[mglev].ncorners()];
	cres_sf[lev].resize(lev_interface[mglev].ncorners());
	cres_sc[lev].resize(lev_interface[mglev].ncorners());
	cres_df[lev].resize(lev_interface[mglev].ncorners());
	cres_dc[lev].resize(lev_interface[mglev].ncorners());
	cres_flag[lev] = new int[lev_interface[mglev].ncorners()];
	build_sync_cache(mglev, lev);
    }
}

void holy_grail_amr_multigrid::delete_sync_caches()
{
    for (int lev = lev_min + 1; lev <= lev_max; lev++) 
    {
	int mglev = ml_index[lev];
	delete [] fres_fbox[lev];
	delete [] fres_cbox[lev];
	delete [] fres_creg[lev];
	delete [] fres_sfbox[lev];
	delete [] fres_scbox[lev];
	for (int i = 0; i < lev_interface[mglev].nfaces(); i++) 
	{
	    if (fres_flag[lev][i] == 0) delete fres_sc[lev].remove(i);
	}
	for (int i = 0; i < lev_interface[mglev].nfaces(); i++) 
	{
	    if (fres_flag[lev][i] == 0) delete fres_dc[lev].remove(i);
	}
	delete [] fres_flag[lev];
#if (BL_SPACEDIM == 3)
	delete [] eres_fbox[lev];
	delete [] eres_cbox[lev];
	delete [] eres_creg[lev];
	delete [] eres_sfbox[lev];
	delete [] eres_scbox[lev];
	for (int i = 0; i < lev_interface[mglev].nedges(); i++) 
	{
	    if (eres_sf[lev].defined(i)) delete eres_sf[lev].remove(i);
	    if (eres_flag[lev][i] == 0)  delete eres_sc[lev].remove(i);
	}
	for (int i = 0; i < lev_interface[mglev].nedges(); i++) 
	{
	    if (eres_df[lev].defined(i)) delete eres_df[lev].remove(i);
	    if (eres_flag[lev][i] == 0)  delete eres_dc[lev].remove(i);
	}
	delete [] eres_flag[lev];
#endif
	delete [] cres_fbox[lev];
	delete [] cres_cbox[lev];
	delete [] cres_creg[lev];
	delete [] cres_sfbox[lev];
	delete [] cres_scbox[lev];
	for (int i = 0; i < lev_interface[mglev].ncorners(); i++) 
	{
	    if (cres_sf[lev].defined(i)) delete cres_sf[lev].remove(i);
	    if (cres_flag[lev][i] == 0)  delete cres_sc[lev].remove(i);
	}
	for (int i = 0; i < lev_interface[mglev].ncorners(); i++) 
	{
	    if (cres_df[lev].defined(i)) delete cres_df[lev].remove(i);
	    if (cres_flag[lev][i] == 0)  delete cres_dc[lev].remove(i);
	}
	delete [] cres_flag[lev];
    }
    if (lev_min < lev_max) 
    {
	delete [] fres_fbox;
	delete [] fres_cbox;
	delete [] fres_creg;
	delete [] fres_sfbox;
	delete [] fres_scbox;
	delete [] fres_sc;
	delete [] fres_dc;
	delete [] fres_flag;
#if (BL_SPACEDIM == 3)
	delete [] eres_fbox;
	delete [] eres_cbox;
	delete [] eres_creg;
	delete [] eres_sfbox;
	delete [] eres_scbox;
	delete [] eres_sf;
	delete [] eres_sc;
	delete [] eres_df;
	delete [] eres_dc;
	delete [] eres_flag;
#endif
	delete [] cres_fbox;
	delete [] cres_cbox;
	delete [] cres_creg;
	delete [] cres_sfbox;
	delete [] cres_scbox;
	delete [] cres_sf;
	delete [] cres_sc;
	delete [] cres_df;
	delete [] cres_dc;
	delete [] cres_flag;
    }
}

void holy_grail_amr_multigrid::build_sync_cache(int mglev, int lev)
{
    const IntVect& rat = gen_ratio[lev-1];
    const int mglevc = ml_index[lev-1];
    
    const int ncomp = (m_hg_terrain)? 2*BL_SPACEDIM-1 : 1;
    const amr_boundary_class* bndry = (m_hg_terrain)? boundary.terrain_sigma() : boundary.scalar();
    
    for (int iface = 0; iface < lev_interface[mglev].nfaces(); iface++) 
    {
	// find a fine grid touching this face
	int igrid = lev_interface[mglev].fgrid(iface, 0);
	if (igrid < 0)
	    igrid = lev_interface[mglev].fgrid(iface, 1);
	const unsigned int geo = lev_interface[mglev].fgeo(iface);
	// reject fine-fine interfaces and those without an interior fine grid
	if (geo == level_interface::ALL || igrid < 0 || lev_interface[mglev].fflag(iface) ) 
	{
	    fres_flag[lev][iface] = 1; // means "fres_dc[lev][iface] not allocated"
	    continue;
	}
	// fine grid on just one side
	int idim = lev_interface[mglev].fdim(iface);
	int idir = (geo & level_interface::LOW) ? -1 : 1;
	Box& fbox = fres_fbox[lev][iface];
	Box& cbox = fres_cbox[lev][iface];
	Box& creg = fres_creg[lev][iface];
	fbox = dest[lev][igrid].box();
	cbox = lev_interface[mglev].node_face(iface);
	cbox.coarsen(rat);
	if (idir > 0)
	    cbox.growLo(idim, 1);
	else
	    cbox.growHi(idim, 1);
	int cgrid = find_patch(cbox, dest[lev-1], 0);
	Box& sigmafbox = fres_sfbox[lev][iface];
	Box& sigmacbox = fres_scbox[lev][iface];
	sigmafbox = sigma[mglev][igrid].box();
	sigmacbox = cbox;
	sigmacbox.convert(IntVect::TheCellVector());
	if (cgrid >= 0) 
	{
	    fres_sc[lev].set(iface, &sigma[mglevc][cgrid]);
	    sigmacbox = fres_sc[lev][iface].box();
	}
	else 
	{
	    fres_sc[lev].set(iface, new FArrayBox(sigmacbox, ncomp));
	    fill_patch(fres_sc[lev][iface], fres_sc[lev][iface].box(), sigma[mglevc], lev_interface[mglevc], bndry, 0);
	}
	if (cgrid >= 0) 
	{
	    fres_dc[lev].set(iface, &dest[lev-1][cgrid]);
	    cbox = fres_dc[lev][iface].box();
	    fres_flag[lev][iface] = 1;
	}
	else 
	{
	    fres_dc[lev].set(iface, new FArrayBox(cbox));
	    fres_flag[lev][iface] = 0;
	}
	IntVect t = lev_interface[mglev].face(iface).type();
	creg = lev_interface[mglev].node_face(iface);
	creg.coarsen(rat).grow(t - IntVect::TheUnitVector());
    }
    
#if (BL_SPACEDIM == 3)
    
    for (int iedge = 0; iedge < lev_interface[mglev].nedges(); iedge++) 
    {
	// find a fine grid touching this edge
	int igrid;
	for (int i = 0; i < level_interface::N_EDGE_GRIDS; i++) 
	{
	    igrid = lev_interface[mglev].egrid(iedge, i);
	    if (igrid >= 0)
		break;
	}
	const unsigned int geo = lev_interface[mglev].geo(1, iedge);
	// reject fine-fine interfaces and those without an interior fine grid
	if (geo == level_interface::ALL || igrid < 0 || lev_interface[mglev].flag(1, iedge) ) 
	{
	    eres_flag[lev][iedge] = 1; // means "eres_dc[lev][iedge] not allocated"
	    continue;
	}
	Box& fbox = eres_fbox[lev][iedge];
	Box& cbox = eres_cbox[lev][iedge];
	Box& creg = eres_creg[lev][iedge];
	IntVect t = lev_interface[mglev].edge(iedge).type();
	cbox = lev_interface[mglev].node_edge(iedge);
	cbox.coarsen(rat).grow(t);
	fbox = refine(cbox, rat);
	eres_df[lev].set(iedge, new FArrayBox(fbox));
	int cgrid = find_patch(cbox, dest[lev-1], 0);
	Box& sigmafbox = eres_sfbox[lev][iedge];
	Box& sigmacbox = eres_scbox[lev][iedge];
	sigmafbox = fbox;
	sigmafbox.convert(IntVect::TheCellVector());
	eres_sf[lev].set(iedge, new FArrayBox(sigmafbox, ncomp));
	fill_patch(eres_sf[lev][iedge], eres_sf[lev][iedge].box(), sigma[mglev], lev_interface[mglev], bndry, 0, 1, iedge);
	sigmacbox = cbox;
	sigmacbox.convert(IntVect::TheCellVector());
	if (cgrid >= 0) 
	{
	    eres_sc[lev].set(iedge, &sigma[mglevc][cgrid]);
	    sigmacbox = eres_sc[lev][iedge].box();
	}
	else 
	{
	    eres_sc[lev].set(iedge, new FArrayBox(sigmacbox, ncomp));
	    fill_patch(eres_sc[lev][iedge], eres_sc[lev][iedge].box(), sigma[mglevc], lev_interface[mglevc], bndry, 0);
	}
	if (cgrid >= 0) 
	{
	    eres_dc[lev].set(iedge, &dest[lev-1][cgrid]);
	    cbox = eres_dc[lev][iedge].box();
	    eres_flag[lev][iedge] = 1;
	}
	else 
	{
	    eres_dc[lev].set(iedge, new FArrayBox(cbox));
	    eres_flag[lev][iedge] = 0;
	}
	creg = lev_interface[mglev].node_edge(iedge);
	creg.coarsen(rat).grow(t - IntVect::TheUnitVector());
    }
    
#endif
    
    for (int icor = 0; icor < lev_interface[mglev].ncorners(); icor++) 
    {
	// find a fine grid touching this corner
	int igrid;
	for (int i = 0; i < level_interface::N_CORNER_GRIDS; i++) 
	{
	    igrid = lev_interface[mglev].cgrid(icor, i);
	    if (igrid >= 0)
		break;
	}
	const unsigned int geo = lev_interface[mglev].geo(0, icor);
	// reject fine-fine interfaces and those without an interior fine grid
	if (geo == level_interface::ALL || igrid < 0 || lev_interface[mglev].flag(0, icor) ) 
	{
	    cres_flag[lev][icor] = 1; // means "cres_dc[lev][icor] not allocated"
	    continue;
	}
	Box& fbox = cres_fbox[lev][icor];
	Box& cbox = cres_cbox[lev][icor];
	Box& creg = cres_creg[lev][icor];
	cbox = lev_interface[mglev].corner(icor);
	fbox = lev_interface[mglev].corner(icor);
	cbox.coarsen(rat).grow(1);
	fbox.grow(rat);
	cres_df[lev].set(icor, new FArrayBox(fbox));
	int cgrid = find_patch(cbox, dest[lev-1], 0);
	Box& sigmafbox = cres_sfbox[lev][icor];
	Box& sigmacbox = cres_scbox[lev][icor];
	sigmafbox = fbox;
	sigmafbox.convert(IntVect::TheCellVector());
	cres_sf[lev].set(icor, new FArrayBox(sigmafbox, ncomp));
	fill_patch(cres_sf[lev][icor], cres_sf[lev][icor].box(), sigma[mglev], lev_interface[mglev], bndry, 0, 0, icor);
	sigmacbox = cbox;
	sigmacbox.convert(IntVect::TheCellVector());
	if (cgrid >= 0) 
	{
	    cres_sc[lev].set(icor, &sigma[mglevc][cgrid]);
	    sigmacbox = cres_sc[lev][icor].box();
	}
	else 
	{
	    cres_sc[lev].set(icor, new FArrayBox(sigmacbox, ncomp));
	    fill_patch(cres_sc[lev][icor], cres_sc[lev][icor].box(), sigma[mglevc], lev_interface[mglevc], bndry, 0);
	}
	if (cgrid >= 0) 
	{
	    cres_dc[lev].set(icor, &dest[lev-1][cgrid]);
	    cbox = cres_dc[lev][icor].box();
	    cres_flag[lev][icor] = 1;
	}
	else 
	{
	    cres_dc[lev].set(icor, new FArrayBox(cbox));
	    cres_flag[lev][icor] = 0;
	}
	creg = lev_interface[mglev].corner(icor);
	creg.coarsen(rat);
    }
}

void holy_grail_amr_multigrid::interface_residual(int mglev, int lev)
{ 
    const Real hx = h[mglev][0];
    const Real hy = h[mglev][1];
#if (BL_SPACEDIM == 3)
    const Real hz = h[mglev][2];
#endif
    
    const IntVect& rat = gen_ratio[lev-1];
    const int mglevc = ml_index[lev-1];
    
    // PARALLEL TODO
    for (int iface = 0; iface < lev_interface[mglev].nfaces(); iface++) 
    {
	// find a fine grid touching this face
	int igrid = lev_interface[mglev].fgrid(iface, 0);
	if (igrid < 0)
	    igrid = lev_interface[mglev].fgrid(iface, 1);
	const unsigned int geo = lev_interface[mglev].fgeo(iface);
	// reject fine-fine interfaces and those without an interior fine grid
	if (geo == level_interface::ALL || igrid < 0 || lev_interface[mglev].fflag(iface) )
	    continue;
	// fine grid on just one side
	const int idim = lev_interface[mglev].fdim(iface);
	const int idir = (geo & level_interface::LOW) ? -1 : 1;
	const Box& sbox = source[lev][igrid].box();
	const Box& fbox = fres_fbox[lev][iface];
	const Box& cbox = fres_cbox[lev][iface];
	const Box& sigmafbox = fres_sfbox[lev][iface];
	const Box& sigmacbox = fres_scbox[lev][iface];
	FArrayBox& sigmac = fres_sc[lev][iface];
	Real* sigmafptr = sigma[mglev][igrid].dataPtr();
	const Box& creg = fres_creg[lev][iface];
	FArrayBox& cdst = fres_dc[lev][iface];
	if (fres_flag[lev][iface] == 0) 
	{
	    fill_patch(cdst, cdst.box(), dest[lev-1], lev_interface[mglevc], boundary.pressure(), 0);
	}
	Real* rptr = resid[mglev][igrid].dataPtr();
	Real* sptr = source[lev][igrid].dataPtr();
	Real* dptr = dest[lev][igrid].dataPtr();
	if (m_hg_terrain)
	{
	    FORT_HGFRES_TERRAIN(rptr, DIMLIST(sbox),
		sptr, DIMLIST(sbox),
		dptr, DIMLIST(fbox),
		cdst.dataPtr(), DIMLIST(cbox),
		sigmafptr, DIMLIST(sigmafbox),
		sigmac.dataPtr(), DIMLIST(sigmacbox),
		DIMLIST(creg),
		D_DECL(rat[0], rat[1], rat[2]), &idim, &idir
		);
	}
	else if (m_hg_full_stencil)
	{
#if BL_SPACEDIM != 3
	    const int isRZ = IsRZ();
	    const int imax = mg_domain[mglevc].bigEnd(0) + 1;
	    FORT_HGFRES_FULL_STENCIL(rptr, DIMLIST(sbox),
		sptr, DIMLIST(sbox),
		dptr, DIMLIST(fbox),
		cdst.dataPtr(), DIMLIST(cbox),
		sigmafptr, DIMLIST(sigmafbox),
		sigmac.dataPtr(), DIMLIST(sigmacbox),
		DIMLIST(creg),
		&hx, &hy,
		rat[0], rat[1], &idim, &idir,
		&isRZ, &imax
		);
#endif
	}
	else
	{
	    FORT_HGFRES(rptr, DIMLIST(sbox),
		sptr, DIMLIST(sbox),
		dptr, DIMLIST(fbox),
		cdst.dataPtr(), DIMLIST(cbox),
		sigmafptr, DIMLIST(sigmafbox),
		sigmac.dataPtr(), DIMLIST(sigmacbox),
		DIMLIST(creg),
		D_DECL(&hx, &hy, &hz),
		D_DECL(rat[0], rat[1], rat[2]), &idim, &idir
		);
	}
    }
    
    if (m_hg_cross_stencil || m_hg_terrain)
    {
	
	int ga[level_interface::N_CORNER_GRIDS];
	
#if (BL_SPACEDIM == 3)
	
	// PARALLEL TODO
	for (int iedge = 0; iedge < lev_interface[mglev].nedges(); iedge++) 
	{
	    // find a fine grid touching this edge
	    int igrid;
	    for (int i = 0; i < level_interface::N_EDGE_GRIDS; i++) 
	    {
		igrid = lev_interface[mglev].egrid(iedge, i);
		if (igrid >= 0)
		    break;
	    }
	    const unsigned int geo = lev_interface[mglev].geo(1, iedge);
	    // reject fine-fine interfaces and those without an interior fine grid
	    if (geo != level_interface::ALL && igrid >= 0 && !lev_interface[mglev].flag(1, iedge) ) 
	    {
		const Box& sbox = source[lev][igrid].box();
		const Box& fbox = eres_fbox[lev][iedge];
		const Box& cbox = eres_cbox[lev][iedge];
		const Box& sigmafbox = eres_sfbox[lev][iedge];
		const Box& sigmacbox = eres_scbox[lev][iedge];
		FArrayBox& sigmaf = eres_sf[lev][iedge];
		FArrayBox& sigmac = eres_sc[lev][iedge];
		const Box& creg = eres_creg[lev][iedge];
		IntVect t = lev_interface[mglev].edge(iedge).type();
		FArrayBox& fdst = eres_df[lev][iedge];
		fill_patch(fdst, fdst.box(), dest[lev], lev_interface[mglev], boundary.pressure(), 0, 1, iedge);
		FArrayBox& cdst = eres_dc[lev][iedge];
		if (eres_flag[lev][iedge] == 0) 
		{
		    fill_patch(cdst, cdst.box(), dest[lev-1], lev_interface[mglevc], boundary.pressure(), 0);
		}
		Real* rptr = resid[mglev][igrid].dataPtr();
		Real* sptr = source[lev][igrid].dataPtr();
		lev_interface[mglev].geo_array(ga, 1, iedge);
		if (m_hg_terrain)
		{
		    FORT_HGERES_TERRAIN(rptr, DIMLIST(sbox),
			sptr, DIMLIST(sbox),
			fdst.dataPtr(), DIMLIST(fbox),
			cdst.dataPtr(), DIMLIST(cbox),
			sigmaf.dataPtr(), DIMLIST(sigmafbox),
			sigmac.dataPtr(), DIMLIST(sigmacbox),
			DIMLIST(creg),
			rat[0], rat[1], rat[2],
			t.getVect(), ga);
		}
		else
		{
		    FORT_HGERES(rptr, DIMLIST(sbox),
			sptr, DIMLIST(sbox),
			fdst.dataPtr(), DIMLIST(fbox),
			cdst.dataPtr(), DIMLIST(cbox),
			sigmaf.dataPtr(), DIMLIST(sigmafbox),
			sigmac.dataPtr(), DIMLIST(sigmacbox),
			DIMLIST(creg),
			&hx, &hy, &hz, rat[0], rat[1], rat[2],
			t.getVect(), ga);
		}
		// fill in the grids on the other sides, if any
		const Box& freg = lev_interface[mglev].node_edge(iedge);
		for (int i = 1; i < level_interface::N_EDGE_GRIDS; i++) 
		{
		    const int jgrid = lev_interface[mglev].egrid(iedge, i);
		    if (jgrid >= 0 && jgrid != igrid)
			internal_copy(resid[mglev], jgrid, igrid, freg);
		}
	    }
	}
	
#endif
	
	// PARALLEL TODO
	for (int icor = 0; icor < lev_interface[mglev].ncorners(); icor++) 
	{
	    // find a fine grid touching this corner
	    int igrid;
	    for (int i = 0; i < level_interface::N_CORNER_GRIDS; i++) 
	    {
		igrid = lev_interface[mglev].cgrid(icor, i);
		if (igrid >= 0)
		    break;
	    }
	    const unsigned int geo = lev_interface[mglev].geo(0, icor);
	    // reject fine-fine interfaces and those without an interior fine grid
	    if (geo != level_interface::ALL && igrid >= 0 && !lev_interface[mglev].flag(0, icor) ) 
	    {
		const Box& sbox = source[lev][igrid].box();
		const Box& fbox = cres_fbox[lev][icor];
		const Box& cbox = cres_cbox[lev][icor];
		const Box& sigmafbox = cres_sfbox[lev][icor];
		const Box& sigmacbox = cres_scbox[lev][icor];
		FArrayBox& sigmaf = cres_sf[lev][icor];
		FArrayBox& sigmac = cres_sc[lev][icor];
		const Box& creg = cres_creg[lev][icor];
		FArrayBox& fdst = cres_df[lev][icor];
		fill_patch(fdst, fdst.box(), dest[lev], lev_interface[mglev], boundary.pressure(), 0, 0, icor);
		FArrayBox& cdst = cres_dc[lev][icor];
		if (cres_flag[lev][icor] == 0) 
		{
		    fill_patch(cdst, cdst.box(), dest[lev-1], lev_interface[mglevc], boundary.pressure(), 0);
		}
		Real * rptr = resid[mglev][igrid].dataPtr();
		Real * sptr = source[lev][igrid].dataPtr();
		lev_interface[mglev].geo_array(ga, 0, icor);
		if (m_hg_terrain)
		{
		    FORT_HGCRES_TERRAIN(rptr, DIMLIST(sbox),
			sptr, DIMLIST(sbox),
			fdst.dataPtr(), DIMLIST(fbox),
			cdst.dataPtr(), DIMLIST(cbox),
			sigmaf.dataPtr(), DIMLIST(sigmafbox),
			sigmac.dataPtr(), DIMLIST(sigmacbox),
			DIMLIST(creg),
			D_DECL(rat[0], rat[1], rat[2]),
			ga);
		}
		else
		{
		    FORT_HGCRES(rptr, DIMLIST(sbox),
			sptr, DIMLIST(sbox),
			fdst.dataPtr(), DIMLIST(fbox),
			cdst.dataPtr(), DIMLIST(cbox),
			sigmaf.dataPtr(), DIMLIST(sigmafbox),
			sigmac.dataPtr(), DIMLIST(sigmacbox),
			DIMLIST(creg),
			D_DECL(&hx, &hy, &hz), D_DECL(rat[0], rat[1], rat[2]),
			ga);
		}
		// fill in the grids on the other sides, if any
		const Box& freg = lev_interface[mglev].corner(icor);
		for (int i = 1; i < level_interface::N_CORNER_GRIDS; i++) 
		{
		    const int jgrid = lev_interface[mglev].cgrid(icor, i);
		    if (jgrid >= 0 && jgrid != igrid)
			internal_copy(resid[mglev], jgrid, igrid, freg);
		}
	    }
	}
    }
    else if (m_hg_full_stencil)
    {
#if BL_SPACEDIM != 3
	// PARALLEL TODO
	for (int icor = 0; icor < lev_interface[mglev].ncorners(); icor++) 
	{
	    // find a fine grid touching this corner
	    int igrid;
	    for (int i = 0; i < level_interface::N_CORNER_GRIDS; i++) 
	    {
		igrid = lev_interface[mglev].cgrid(icor, i);
		if (igrid >= 0)
		    break;
	    }
	    const unsigned int geo = lev_interface[mglev].geo(0, icor);
	    // reject fine-fine interfaces and those without an interior fine grid
	    if (geo == level_interface::ALL || igrid < 0 || lev_interface[mglev].flag(0, icor) )
		continue;
	    else if (geo == level_interface::XL || geo == level_interface::XH || geo == level_interface::YL || geo == level_interface::YH) 
	    {
		// fine grid on two adjacent sides
		const int idim = (geo == level_interface::XL || geo == level_interface::XH) ? 0 : 1;
		const int idir = (geo & level_interface::LL) ? -1 : 1;
		const Box& sbox = source[lev][igrid].box();
		const Box& fbox = cres_fbox[lev][icor];
		const Box& cbox = cres_cbox[lev][icor];
		const Box& sigmafbox = cres_sfbox[lev][icor];
		const Box& sigmacbox = cres_scbox[lev][icor];
		FArrayBox& sigmaf = cres_sf[lev][icor];
		FArrayBox& sigmac = cres_sc[lev][icor];
		const Box& creg = cres_creg[lev][icor];
		FArrayBox& fdst = cres_df[lev][icor];
		fill_patch(fdst, fdst.box(), dest[lev], lev_interface[mglev], boundary.pressure(), 0, 0, icor);
		FArrayBox& cdst = cres_dc[lev][icor];
		if (cres_flag[lev][icor] == 0) 
		{
		    fill_patch(cdst, cdst.box(), dest[lev-1], lev_interface[mglevc], boundary.pressure(), 0, 0, -1);
		}
		Real * rptr = resid[mglev][igrid].dataPtr();
		Real * sptr = source[lev][igrid].dataPtr();
		const int isRZ = IsRZ();
		const int imax = mg_domain[mglevc].bigEnd(0) + 1;
		FORT_HGFRES_FULL_STENCIL(rptr, DIMLIST(sbox),
		    sptr, DIMLIST(sbox),
		    fdst.dataPtr(), DIMLIST(fbox),
		    cdst.dataPtr(), DIMLIST(cbox),
		    sigmaf.dataPtr(), DIMLIST(sigmafbox),
		    sigmac.dataPtr(), DIMLIST(sigmacbox),
		    DIMLIST(creg),
		    &hx, &hy,
		    rat[0], rat[1], &idim, &idir,
		    &isRZ, &imax
		    );
		// fill in the grids on the other sides, if any
		const Box& freg = lev_interface[mglev].corner(icor);
		for (int i = 1; i < level_interface::N_CORNER_GRIDS; i++) 
		{
		    const int jgrid = lev_interface[mglev].cgrid(icor, i);
		    if (jgrid >= 0 && jgrid != igrid)
			internal_copy(resid[mglev], jgrid, igrid, freg);
		}
	    }
	    else if (geo == level_interface::LL || geo == level_interface::HL || geo == level_interface::LH || geo == level_interface::HH) 
	    {
		// outside corner
		int idir0 = (geo & level_interface::XL) ? -1 : 1;
		int idir1 = (geo & level_interface::YL) ? -1 : 1;
		const Box& sbox = source[lev][igrid].box();
		const Box& cbox = cres_cbox[lev][icor];
		const Box& sigmafbox = cres_sfbox[lev][icor];
		const Box& sigmacbox = cres_scbox[lev][icor];
		FArrayBox& sigmaf = cres_sf[lev][icor];
		FArrayBox& sigmac = cres_sc[lev][icor];
		const Box& creg = cres_creg[lev][icor];
		FArrayBox& cdst = cres_dc[lev][icor];
		if (cres_flag[lev][icor] == 0) 
		{
		    fill_patch(cdst, cdst.box(), dest[lev-1], lev_interface[mglevc], boundary.pressure(), 0);
		}
		Real* rptr = resid[mglev][igrid].dataPtr();
		Real* sptr = source[lev][igrid].dataPtr();
		const Box& fbox = dest[lev][igrid].box();
		Real* dptr = dest[lev][igrid].dataPtr();
		const int isRZ = IsRZ();
		FORT_HGORES(rptr, DIMLIST(sbox),
		    sptr, DIMLIST(sbox),
		    dptr, DIMLIST(fbox),
		    cdst.dataPtr(), DIMLIST(cbox),
		    sigmaf.dataPtr(), DIMLIST(sigmafbox),
		    sigmac.dataPtr(), DIMLIST(sigmacbox),
		    DIMLIST(creg),
		    &hx, &hy,
		    rat[0], rat[1], &idir0, &idir1, &isRZ
		    );
	    }
	    else if (geo == (level_interface::LL | level_interface::HH) || geo == (level_interface::LH | level_interface::HL)) 
	    {
		// diagonal corner
		const int jdir = (geo == (level_interface::LL | level_interface::HH)) ? 1 : -1;
		const Box& sbox = source[lev][igrid].box();
		const Box& fbox = cres_fbox[lev][icor];
		const Box& cbox = cres_cbox[lev][icor];
		const Box& sigmafbox = cres_sfbox[lev][icor];
		const Box& sigmacbox = cres_scbox[lev][icor];
		FArrayBox& sigmaf = cres_sf[lev][icor];
		FArrayBox& sigmac = cres_sc[lev][icor];
		const Box& creg = cres_creg[lev][icor];
		FArrayBox& fdst = cres_df[lev][icor];
		fill_patch(fdst, fdst.box(), dest[lev], lev_interface[mglev], boundary.pressure(), 0, 0, icor);
		FArrayBox& cdst = cres_dc[lev][icor];
		if (cres_flag[lev][icor] == 0) 
		{
		    fill_patch(cdst, cdst.box(), dest[lev-1], lev_interface[mglevc], boundary.pressure(), 0, 0, -1);
		}
		Real* rptr = resid[mglev][igrid].dataPtr();
		Real* sptr = source[lev][igrid].dataPtr();
		const int isRZ = IsRZ();
		FORT_HGDRES(rptr, DIMLIST(sbox),
		    sptr, DIMLIST(sbox),
		    fdst.dataPtr(), DIMLIST(fbox),
		    cdst.dataPtr(), DIMLIST(cbox),
		    sigmaf.dataPtr(), DIMLIST(sigmafbox),
		    sigmac.dataPtr(), DIMLIST(sigmacbox),
		    DIMLIST(creg),
		    &hx, &hy,
		    rat[0], rat[1], &jdir, &isRZ
		    );
		// fill in the grids on the other sides, if any
		const Box& freg = lev_interface[mglev].corner(icor);
		for (int i = 1; i < level_interface::N_CORNER_GRIDS; i++) 
		{
		    int jgrid = lev_interface[mglev].cgrid(icor, i);
		    if (jgrid >= 0 && jgrid != igrid)
			internal_copy(resid[mglev], jgrid, igrid, freg);
		}
	    }
	    else 
	    {
		// inside corner
		int idir0 = ((geo & level_interface::XL) == level_interface::XL) ? -1 : 1;
		int idir1 = ((geo & level_interface::YL) == level_interface::YL) ? -1 : 1;
		const Box& sbox = source[lev][igrid].box();
		const Box& fbox = cres_fbox[lev][icor];
		const Box& cbox = cres_cbox[lev][icor];
		const Box& sigmafbox = cres_sfbox[lev][icor];
		const Box& sigmacbox = cres_scbox[lev][icor];
		FArrayBox& sigmaf = cres_sf[lev][icor];
		FArrayBox& sigmac = cres_sc[lev][icor];
		const Box& creg = cres_creg[lev][icor];
		FArrayBox& fdst = cres_df[lev][icor];
		fill_patch(fdst, fdst.box(), dest[lev], lev_interface[mglev], boundary.pressure(), 0, 0, icor);
		FArrayBox& cdst = cres_dc[lev][icor];
		if (cres_flag[lev][icor] == 0) 
		{
		    fill_patch(cdst, cdst.box(), dest[lev-1], lev_interface[mglevc], boundary.pressure(), 0, 0, -1);
		}
		Real* rptr = resid[mglev][igrid].dataPtr();
		Real* sptr = source[lev][igrid].dataPtr();
		const int isRZ = IsRZ();
		FORT_HGIRES(rptr, DIMLIST(sbox),
		    sptr, DIMLIST(sbox),
		    fdst.dataPtr(), DIMLIST(fbox),
		    cdst.dataPtr(), DIMLIST(cbox),
		    sigmaf.dataPtr(), DIMLIST(sigmafbox),
		    sigmac.dataPtr(), DIMLIST(sigmacbox),
		    DIMLIST(creg),
		    &hx, &hy,
		    rat[0], rat[1], &idir0, &idir1, &isRZ
		    );
		// fill in the grids on the other sides, if any
		const Box& freg = lev_interface[mglev].corner(icor);
		int kgrid = -1;
		for (int i = 1; i < level_interface::N_CORNER_GRIDS; i++) 
		{
		    int jgrid = lev_interface[mglev].cgrid(icor, i);
		    if (jgrid >= 0 && jgrid != igrid && jgrid != kgrid) 
		    {
			internal_copy(resid[mglev], jgrid, igrid, freg);
			kgrid = jgrid;
		    }
		}
	    }
        }
#endif
    }
}
