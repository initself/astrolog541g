/************************************************************
   $Header: sweph.h,v 1.27 98/12/02 19:17:57 dieter Exp $
   definitions and constants SWISSEPH

  Authors: Dieter Koch and Alois Treindl, Astrodienst Z�rich

************************************************************/
/* Copyright (C) 1997, 1998 Astrodienst AG, Switzerland.  All rights reserved.
  
  This file is part of Swiss Ephemeris Free Edition.
  
  Swiss Ephemeris is distributed with NO WARRANTY OF ANY KIND.  No author
  or distributor accepts any responsibility for the consequences of using it,
  or for whether it serves any particular purpose or works at all, unless he
  or she says so in writing.  Refer to the Swiss Ephemeris Public License
  ("SEPL" or the "License") for full details.
  
  Every copy of Swiss Ephemeris must include a copy of the License,
  normally in a plain ASCII text file named LICENSE.  The License grants you
  the right to copy, modify and redistribute Swiss Ephemeris, but only
  under certain conditions described in the License.  Among other things, the
  License requires that the copyright notices and this notice be preserved on
  all copies.

  For uses of the Swiss Ephemeris which do not fall under the definitions
  laid down in the Public License, the Swiss Ephemeris Professional Edition
  must be purchased by the developer before he/she distributes any of his
  software or makes available any product or service built upon the use of
  the Swiss Ephemeris.

  Authors of the Swiss Ephemeris: Dieter Koch and Alois Treindl

  The authors of Swiss Ephemeris have no control or influence over any of
  the derived works, i.e. over software or services created by other
  programmers which use Swiss Ephemeris functions.

  The names of the authors or of the copyright holder (Astrodienst) must not
  be used for promoting any software, product or service which uses or contains
  the Swiss Ephemeris. This copyright notice is the ONLY place where the
  names of the authors can legally appear, except in cases where they have
  given special permission in writing.

  The trademarks 'Swiss Ephemeris' and 'Swiss Ephemeris inside' may be used
  for promoting such software, products or services.
*/

/*
 * move over from swephexp.h
 */

#define J2000           2451545.0  	/* 2000 January 1.5 */
#define B1950           2433282.42345905  	/* 1950 January 0.923 */
#define J1900           2415020.0  	/* 1900 January 0.5 */

#define MPC_CERES       1
#define MPC_PALLAS      2
#define MPC_JUNO        3
#define MPC_VESTA       4
#define MPC_CHIRON      2060
#define MPC_PHOLUS      5145

#define SE_NAME_SUN             "Sun"
#define SE_NAME_MOON            "Moon"
#define SE_NAME_MERCURY         "Mercury"
#define SE_NAME_VENUS           "Venus"
#define SE_NAME_MARS            "Mars"
#define SE_NAME_JUPITER         "Jupiter"
#define SE_NAME_SATURN          "Saturn"
#define SE_NAME_URANUS          "Uranus"
#define SE_NAME_NEPTUNE         "Neptune"
#define SE_NAME_PLUTO           "Pluto"
#define SE_NAME_MEAN_NODE       "mean Node"
#define SE_NAME_TRUE_NODE       "true Node"
#define SE_NAME_MEAN_APOG       "mean Apogee"
#define SE_NAME_OSCU_APOG       "osc. Apogee"
#define SE_NAME_EARTH           "Earth"
#define SE_NAME_CERES           "Ceres"
#define SE_NAME_PALLAS          "Pallas"
#define SE_NAME_JUNO            "Juno"
#define SE_NAME_VESTA           "Vesta"
#define SE_NAME_CHIRON          "Chiron"
#define SE_NAME_PHOLUS          "Pholus"

 
#define SE_NAME_CUPIDO          "Cupido"
#define SE_NAME_HADES           "Hades"
#define SE_NAME_ZEUS            "Zeus"
#define SE_NAME_KRONOS          "Kronos"
#define SE_NAME_APOLLON         "Apollon"
#define SE_NAME_ADMETOS         "Admetos"
#define SE_NAME_VULKANUS        "Vulkanus"
#define SE_NAME_POSEIDON        "Poseidon"
#define SE_NAME_ISIS            "Isis"
#define SE_NAME_NIBIRU          "Nibiru"
#define SE_NAME_HARRINGTON      "Harrington"
#define SE_NAME_NEPTUNE_LEVERRIER       "Leverrier"
#define SE_NAME_NEPTUNE_ADAMS   "Adams"
#define SE_NAME_PLUTO_LOWELL    "Lowell"
#define SE_NAME_PLUTO_PICKERING "Pickering"

/* for delta t: tidal acceleration in the mean motion of the moon */
#define SE_TIDAL_DE403          (-25.8)
#define SE_TIDAL_DE404          (-25.8)
#define SE_TIDAL_DE405          (-25.8)
#define SE_TIDAL_DE406          (-25.8)
#define SE_TIDAL_DE200          (-23.8946)
#define SE_TIDAL_26             (-26.0)

#define SE_TIDAL_DEFAULT        SE_TIDAL_DE406


/*
 * earlier content
 */

#define PI              M_PI	/* 3.14159265358979323846, math.h */
#define TWOPI           (2.0 * PI)

#define ENDMARK         -99

#define SEI_EPSILON     -2
#define SEI_NUTATION    -1
#define SEI_EMB		0	
#define SEI_EARTH	0	
#define SEI_SUN  	0	
#define	SEI_MOON	1	
#define	SEI_MERCURY	2	
#define	SEI_VENUS	3	
#define	SEI_MARS	4	
#define	SEI_JUPITER	5	
#define	SEI_SATURN	6	
#define	SEI_URANUS	7	
#define	SEI_NEPTUNE	8	
#define	SEI_PLUTO	9	
#define	SEI_SUNBARY	10	/* barycentric sun */
#define	SEI_ANYBODY	11	/* any asteroid */
#define	SEI_CHIRON	12	
#define	SEI_PHOLUS	13	
#define	SEI_CERES	14	
#define	SEI_PALLAS	15	
#define	SEI_JUNO	16	
#define	SEI_VESTA	17	

#define SEI_NPLANETS    18

#define SEI_MEAN_NODE   0
#define SEI_TRUE_NODE   1
#define SEI_MEAN_APOG   2
#define SEI_OSCU_APOG   3

#define SEI_NNODE_ETC    4

#define SEI_FLG_HELIO   1
#define SEI_FLG_ROTATE  2
#define SEI_FLG_ELLIPSE 4
#define SEI_FLG_EMBHEL  8   	/* TRUE, if heliocentric earth is given
				 * instead of barycentric sun 
				 * i.e. bary sun is computed from 
				 * barycentric and heliocentric earth */

#define SEI_FILE_PLANET	  0
#define SEI_FILE_MOON	  1 
#define SEI_FILE_MAIN_AST 2
#define SEI_FILE_ANY_AST  3
#define SEI_FILE_FIXSTAR  4

#if 0
#define SEI_FILE_TEST_ENDIAN     (97L * 65536L + 98L * 256L + 99L) /*abc*/
#endif
#define SEI_FILE_TEST_ENDIAN     (0x616263L) 	/* abc*/ 
#define SEI_FILE_BIGENDIAN	0
#define SEI_FILE_NOREORD	0
#define SEI_FILE_LITENDIAN	1
#define SEI_FILE_REORD  	2

#define SEI_FILE_NMAXPLAN	50
#define SEI_FILE_EFPOSBEGIN      500

#define SE_FILE_SUFFIX	"se1"

#define SEI_NEPHFILES   7
#define SEI_CURR_FPOS   -1

#define MOSHPLEPH_START	 625000.5
#define MOSHPLEPH_END  	2818000.5
#define MOSHLUEPH_START	 625000.5
#define MOSHLUEPH_END  	2818000.5
#define JPLEPH_START	 625307.5	/* about -3000 (DE406) */
#define JPLEPH_END	2816848.5	/* about  3000 (DE406) */
#define SWIEPH_START	 625614.927151
#define SWIEPH_END	2813641.5
#define ALLEPH_START	MOSHPLEPH_START
#define ALLEPH_END	MOSHPLEPH_END

#define MAXORD          40

#define NCTIES         6.0     /* number of centuries per eph. file */
#define BEG_YEAR       (-3000)
#define END_YEAR       3000

#define OK (0)
#define ERR (-1)
#define NOT_AVAILABLE (-2)
#define BEYOND_EPH_LIMITS (-3)

#define J_TO_J2000   	1
#define J2000_TO_J   	-1

/* we always use Astronomical Almanac constants, if available */
#define MOON_MEAN_DIST  384400000.0		/* in m, AA 1996, F2 */
#define MOON_MEAN_INCL  5.1453964		/* AA 1996, D2 */
#define MOON_MEAN_ECC   0.054900489		/* AA 1996, F2 */
#define EARTH_MOON_MRAT (1 / 0.012300034)	/* AA 1966, K6 */
#if 0
#define EARTH_MOON_MRAT 81.30056		/* de406 */
#endif
#define AUNIT       	1.4959787066e+11  	/* au in meters, AA 1996 K6 */
#if 0
#define AUNIT       	1.49597870691e+11  	/* au in meters, de403-6 */
#endif
#define CLIGHT       	2.99792458e+8   	/* m/s, AA 1996 K6 */
#define HELGRAVCONST    1.32712438e+20		/* G * M(sun), m^3/sec^2, AA 1996 K6 */
#define GEOGCONST       3.98600448e+14 		/* G * M(earth) m^3/sec^2, AA 1996 K6 */
#define KGAUSS		0.01720209895		/* Gaussian gravitational constant K6 */
#define PRECESSCONST    50.290966       	/* AA 1996 K6 */
#define SUN_RADIUS      (959.63 / 3600 * DEGTORAD)  /*  Meeus germ. p 391 */
#define EARTH_RADIUS	6378137.0		/* AA 1998 K13 */
#define EARTH_OBLATENESS (1.0/ 298.257223563)	/* AA 1998 K13 */

#define LIGHTTIME_AUNIT  (499.004782/3600/24) 	/* 8.3167 minutes (days), AA K6 */
#define KM_S_TO_AU_CTY	 21.095			/* km/s to AU/year */
#define MOON_SPEED_INTV  0.00005 		/* 4.32 seconds (in days) */
#define PLAN_SPEED_INTV  0.0001 	        /* 8.64 seconds (in days) */
#define MEAN_NODE_SPEED_INTV  0.001		
#define NODE_CALC_INTV  0.0001		
#define NODE_CALC_INTV_MOSH   0.1		
#define NUT_SPEED_INTV   0.0001
#define DEFL_SPEED_INTV  0.0000005

/* for chopt.c and numint.c, asteroid ephemerides */
#define AST_ELEM_FILE 	"/users/dieter/numint/astorb.dat"
#define AST_DATA_DIR	"/opt/jpl/data/mpc/"

#define square_sum(x)   (x[0]*x[0]+x[1]*x[1]+x[2]*x[2])
#define dot_prod(x,y)   (x[0]*y[0]+x[1]*y[1]+x[2]*y[2])

#define PNOINT2JPL {J_EARTH, J_MOON, J_MERCURY, J_VENUS, J_MARS, J_JUPITER, J_SATURN, J_URANUS, J_NEPTUNE, J_PLUTO, J_SUN,}

#define PLAN_DATA struct plan_data

/* obliquity of ecliptic */
struct epsilon {
  double teps, eps, seps, ceps; 	/* jd, eps, sin(eps), cos(eps) */
};

extern struct epsilon oec2000;
extern struct epsilon oec;

struct plan_data {
  /* the following data are read from file only once, immediately after 
   * file has been opened */
  int ibdy;		/* internal body number */
  long iflg;		/* contains several bit flags describing the data:	
			 * SEI_FLG_HELIO: true if helio, false if bary
			 * SEI_FLG_ROTATE: TRUE if coefficients are referred 
			 *      to coordinate system of orbital plane 
			 * SEI_FLG_ELLIPSE: TRUE if reference ellipse */
  int ncoe;		/* # of coefficients of ephemeris polynomial,
			   is polynomial order + 1  */
  /* where is the segment index on the file */
  long lndx0;   	/* file position of begin of planet's index */
  long nndx;		/* number of index entries on file: computed */
  double tfstart;	/* file contains ephemeris for tfstart thru tfend */
  double tfend;         /*      for this particular planet !!!            */
  double dseg;		/* segment size (days covered by a polynomial)  */
  /* orbital elements: */
  double telem;		/* epoch of elements */
  double prot;		
  double qrot; 
  double dprot;
  double dqrot; 
  double rmax;		/* normalisation factor of cheby coefficients */
  /* in addition, if reference ellipse is used: */
  double peri;		
  double dperi; 
  double *refep;	/* pointer to cheby coeffs of reference ellipse,
			 * size of data is 2 x ncoe */
  /* unpacked segment information, only updated when a segment is read: */
  double tseg0, tseg1;	/* start and end jd of current segment */
  double *segp;         /* pointer to unpacked cheby coeffs of segment;
			 * the size is 3 x ncoe */
  int neval;		/* how many coefficients to evaluate. this may
			 * be less than ncoe */
  /* result of most recent data evaluation for this body: */
  double teval;		/* time for which previous computation was made */
  long iephe;            /* which ephemeris was used */
  double x[6];		/* position and speed vectors equatorial J2000 */
  long xflgs;		/* hel., light-time, aberr., prec. flags etc. */
  double xreturn[24];   /* return positions:
			 * xreturn+0	ecliptic polar coordinates
			 * xreturn+6	ecliptic cartesian coordinates
			 * xreturn+12	equatorial polar coordinates
			 * xreturn+18	equatorial cartesian coordinates
			 */
};

/*
 * stuff exported from swemplan.c and swemmoon.c 
 * and constants used inside these functions.
************************************************************/

#define STR             4.8481368110953599359e-6 /* radians per arc second */

/* moon, s. moshmoon.c */
extern int swi_mean_node(double jd, double *x, char *serr);
extern int swi_mean_apog(double jd, double *x, char *serr);
extern int swi_moshmoon(double tjd, AS_BOOL do_save, double *xpm, char *serr) ;
extern int swi_moshmoon2(double jd, double *x);

/* planets, s. moshplan.c */
extern int swi_moshplan(double tjd, int ipli, AS_BOOL do_save, double *xpret, double *xeret, char *serr);
extern int swi_moshplan2(double J, int iplm, double *pobj);
extern void swi_osc_el_plan(double tjd, double *xp, int ipl, int ipli);
extern FILE *swi_fopen(int ifno, char *fname, char *ephepath, char *serr);

/* nutation */
struct nut {
  double tnut;
  double nutlo[2];	/* nutation in longitude and obliquity */
  double snut, cnut;	/* sine and cosine of nutation in obliquity */
  double matrix[3][3];	
};

struct plantbl {
  char max_harmonic[9];
  char max_power_of_t;
  signed char *arg_tbl;
  double *lon_tbl;
  double *lat_tbl;
  double *rad_tbl;
  double distance;
};

struct file_data {
  char fnam[AS_MAXCH];	/* ephemeris file name */
  int fversion;		/* version number of file */
  char astnam[50];	/* asteroid name, if asteroid file */ 
  long sweph_denum;     /* DE number of JPL ephemeris, which this file
			 * is derived from. */
  FILE *fptr;		/* ephemeris file pointer */
  double tfstart;       /* file may be used from this date */
  double tfend;         /*      through this date          */
  long iflg; 		/* byte reorder flag and little/bigendian flag */
  short npl;		/* how many planets in file */
  short ipl[SEI_FILE_NMAXPLAN];	/* planet numbers */
};
 
struct gen_const {
 double clight, 
	aunit, 
	helgravconst, 
	ratme, 
	sunradius;
};

struct save_positions {
  int ipl;
  double tsave;
  long iflgsave;
  /* position at t = tsave,
   * in ecliptic polar (offset 0),
   *    ecliptic cartesian (offset 6), 
   *    equatorial polar (offset 12),
   *    and equatorial cartesian coordinates (offset 18).
   * 6 doubles each for position and speed coordinates.
   */
  double xsaves[24];    
};

struct node_data {
  /* result of most recent data evaluation for this body: */
  double teval;		/* time for which last computation was made */
  long iephe;            /* which ephemeris was used */
  double x[6];		/* position and speed vectors equatorial J2000 */
  long xflgs;		/* hel., light-time, aberr., prec. flags etc. */
  double xreturn[24];   /* return positions: 
			 * xreturn+0	ecliptic polar coordinates
			 * xreturn+6	ecliptic cartesian coordinates
			 * xreturn+12	equatorial polar coordinates
			 * xreturn+18	equatorial cartesian coordinates
			 */
};

struct topo_data {
  AS_BOOL geopos_is_set;
  double geolon, geolat, geoalt;
  double teval;
  double tjd_ut;
  double xobs[6];
};

struct swe_data {
  char ephepath[AS_MAXCH];
  char jplfnam[AS_MAXCH];
  short jpl_file_is_open;
  struct file_data fidat[SEI_NEPHFILES];
  struct gen_const gcdat;
  struct plan_data pldat[SEI_NPLANETS];
  struct node_data nddat[SEI_NNODE_ETC];
  struct save_positions savedat[SE_NPLANETS+1];
  struct epsilon oec;
  struct epsilon oec2000;
  struct nut nut;
  struct nut nut2000;
  struct nut nutv;
  struct topo_data topd;
};

extern struct swe_data FAR swed;

