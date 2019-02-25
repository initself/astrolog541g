/*
** Astrolog (Version 5.41G) File: io.c
**
** Code changed by Valentin Abramov
**
** IMPORTANT NOTICE: The graphics database and chart display routines
** used in this program are Copyright (C) 1991-1998 by Walter D. Pullen
** (Astara@msn.com, http://www.magitech.com/~cruiser1/astrolog.htm).
** Permission is granted to freely use and distribute these routines
** provided one doesn't sell, restrict, or profit from them in any way.
** Modification is allowed provided these notices remain with any
** altered or edited versions of the program.
**
** The main planetary calculation routines used in this program have
** been Copyrighted and the core of this program is basically a
** conversion to C of the routines created by James Neely as listed in
** Michael Erlewine's 'Manual of Computer Programming for Astrologers',
** available from Matrix Software. The copyright gives us permission to
** use the routines for personal use but not to sell them or profit from
** them in any way.
**
** The PostScript code within the core graphics routines are programmed
** and Copyright (C) 1992-1993 by Brian D. Willoughby
** (brianw@sounds.wa.com). Conditions are identical to those above.
**
** The extended accurate ephemeris databases and formulas are from the
** calculation routines in the library SWISS EPHEMERIS and are programmed and
** copyright 1998 by Astrodienst AG.
** The use of that source code is subject to
** the Swiss Ephemeris Public License, available at 
** http://www.astro.ch/swisseph. This copyright notice must not be 
** changed or removed by any user of this program.
**
** Initial programming 8/28,30, 9/10,13,16,20,23, 10/3,6,7, 11/7,10,21/1991.
** X Window graphics initially programmed 10/23-29/1991.
** PostScript graphics initially programmed 11/29-30/1992.
** Last code change made 12/20/1998.
** Modifications from version 5.40 to 5.41 are by Alois Treindl.
*/

#include "astrolog.h"
#include <string.h>
/*
******************************************************************************
** File IO Routines.
******************************************************************************
*/

/* Open the file indicated by the given string and return the file's stream */
/* pointer, or NULL if the file couldn't be found or opened. All parts of   */
/* the program which open files to read call this routine. We look in       */
/* several various locations and directories for the file before giving up. */

FILE *FileOpen(szFile, nFileMode)
byte *szFile;
int nFileMode;
{
  FILE *file;
  byte name[cchSzDef], mode[3];
#ifdef ENVIRON
  byte *env;
#endif

  /* Some file types we want to open as binary instead of Ascii. */
  sprintf(mode, "r%s", nFileMode == 2 ? "b" : "");

  /* First look for the file in the current directory. */
  file = fopen(szFile, mode);
  if (file != NULL)
    return file;

#ifdef ENVIRON
  /* Next look for the file in the directory indicated by the version */
  /* specific system environment variable.                            */
  sprintf(name, "%s%s", ENVIRONVER, szVersionCore);
  env = getenv(name);
  if (env && *env) {
    sprintf(name, "%s%c%s", env, chDirSep, szFile);
    file = fopen(name, mode);
    if (file != NULL)
      return file;
  }

  /* Next look in the directory in the general environment variable. */
  env = getenv(ENVIRONALL);
  if (env && *env) {
    sprintf(name, "%s%c%s", env, chDirSep, szFile);
    file = fopen(name, mode);
    if (file != NULL)
      return file;
  }

  /* Next look in the directory in the version prefix environment variable. */
  env = getenv(ENVIRONVER);
  if (env && *env) {
    sprintf(name, "%s%c%s", env, chDirSep, szFile);
    file = fopen(name, mode);
    if (file != NULL)
      return file;
  }
#endif

  /* Finally look in one of several directories specified at compile time. */
  sprintf(name, "%s%c%s", nFileMode == 0 ? DEFAULT_DIR :
    (nFileMode == 1 ? CHART_DIR : EPHE_DIR), chDirSep, szFile);
  file = fopen(name, mode);
  if (file == NULL && nFileMode == 1) {
    /* If the file was never found, print an error (unless we were looking */
    /* for a certain file type, e.g. the optional astrolog.dat file).      */
    sprintf(name, "File '%s' not found.", szFile);
    PrintError(name);
  }
  return file;
}


/* This is Astrolog's generic file processing routine, which handles chart */
/* info files, position files, and config files. Given a file name or a    */
/* file handle, run through each line as a series of command switches.     */

bool FProcessSwitchFile(szFile, file)
byte *szFile;
FILE *file;
{
  byte szLine[cchSzMax], *argv[MAXSWITCHES], ch;
  int argc, i;

  if (file == NULL)
    file = FileOpen(szFile, 0);
  if (file == NULL)
    return fFalse;

  /* All files have to begin with the -@ switch file type identifier. */
  ch = getc(file); ungetc(ch, file);
  if (ch != '@') {
    sprintf(szLine,
      "The command file '%s' is not in any valid format (character %d).",
      szFile, (int)ch);
    PrintWarning(szLine);
    return fFalse;
  }

  loop {
    while (!feof(file) && (ch = getc(file)) < ' ')
      ;
    if (feof(file))
      break;
    for (szLine[0] = ch, i = 1; i < cchSzMax && !feof(file) &&
      (szLine[i] = getc(file)) >= ' '; i++)
      ;
    szLine[i] = chNull;
    argc = NParseCommandLine(szLine, argv);
    if (!FProcessSwitches(argc, argv))
      return fFalse;
  }
  return fTrue;
}


/* Take the current chart information, and write it out to the file   */
/* as indicated by the -o switch. This is only executed at the end of */
/* program execution if the -o switch is in effect.                   */

bool FOutputData()
{
  byte sz[cchSzDef];
  FILE *file;
  int i, j;
  real rT;

  if (us.fNoWrite)
    return fFalse;
  file = fopen(is.szFileOut, "w");  /* Create and open the file for output. */
  if (file == NULL) {
    sprintf(sz, "File %s can not be created.", is.szFileOut);
    PrintError(sz);
    return fFalse;
  }
  if (!us.fWritePos) {

    /* Write the chart information to the file. */

    if (Mon < 1) {
      fclose(file);
      PrintError("Can't output chart with no time/space to file.");
      return fFalse;
    }
    if (us.fWriteOld) {
      fprintf(file, "%d\n%d\n%d\n%.2f\n%.2f\n%.2f\n%.2f\n",
        Mon, Day, Yea, Tim, Zon-Dst, Lon, Lat);
    } else {
      fprintf(file, "@0102  ; %s chart info.\n", szAppName);
      i = us.fAnsiChar;
      us.fAnsiChar = fFalse;
      fprintf(file, "%cqb %c%c%c %d %d %s %s %s %s\n", chSwitch, chMon3(Mon),
        Day, Yea, SzTim(Tim), Dst == 0.0 ? "ST" : (Dst == 1.0 ? "DT" :
        SzZone(Dst)), SzZone(-Zon), SzLocation(Lon, Lat));
      fprintf(file, "%czi \"%s\" \"%s\"\n", chSwitch, ciMain.nam, ciMain.loc);
      us.fAnsiChar = i;
    }
  } else {

    /* However, if the -o0 switch is in effect, then write the actual */
    /* positions of the planets and houses to the file instead.       */

    if (us.fWriteOld) {
      for (i = 1; i <= oNorm; i++) {
        j = (int)planet[i];
        fprintf(file, "%c%c%c: %2d %2d %10.7f\n", chObj3(i),
          j%30, j/30+1, RFract(planet[i])*60.0);              /* Position */
        rT = planetalt[i];
        fprintf(file, "[%c]: %3d %12.8f\n",                   /* Altitude */
          ret[i] >= 0.0 ? 'D' : chRet, (int)(RSgn(rT)*
          RFloor(RAbs(rT))), (rT-(real)(int)rT)*60.0);     /* Retrograde? */
        if (i == oNod)
          i = oFor-1;
        else if (i == oFor)
          i = oMC -1;
        else if (i == oMC)
          i = oAsc-1;
        else if (i == oAsc)
          i = oVtx-1;
        else if (i == oVtx)    /* Skip minor cusps to write uranians  */
          i = us.fUranian ? uranLo-1 : cObj;
      }
      for (i = 1; i <= cSign/2; i++) {   /* Write first six cusp positions */
        j = (int)chouse[i];
        fprintf(file, "H_%c: %2d %2d %10.7f\n",
          'a'+i-1, j%30, j/30+1, RFract(chouse[i])*60.0);
      }

    } else {
      fprintf(file, "@0203  ; %s chart positions.\n", szAppName);
      fprintf(file, "%czi \"%s\" \"%s\"\n", chSwitch, ciMain.nam, ciMain.loc);
      for (i = 1; i <= cObj; i++) if (!ignore[i] || FCusp(i)) {
        fprintf(file, "%cYF ", chSwitch);
        if (i <= oNorm)
          fprintf(file, "%c%c%c", chObj3(i));
        else
          fprintf(file, "%3d", i);
        rT = FBetween(i, cuspLo-1+4, cuspLo-1+9) ?
          chouse[i-(cuspLo-1)] : planet[i];
        j = (int)rT;
        fprintf(file, ":%3d %c%c%c%13.9f,%4d%13.9f,",
          j%30, chSig3(j/30+1), RFract(rT)*60.0,
          (int)planetalt[i], RFract(RAbs(planetalt[i]))*60.0);
        rT = i > oNorm ? 999.0 : (i == oMoo && !us.fPlacalc ? 0.0026 :
          RSqr(spacex[i]*spacex[i]+spacey[i]*spacey[i]+spacez[i]*spacez[i]));
        fprintf(file, "%14.9f%14.9f\n", DFromR(ret[i]), rT);
      }
    }
  }

  /* Now write any extra strings that were on the command line after the -o */
  /* specification but before the next switch, to the file as comments.     */

  for (i = 1; i < is.cszComment; i++) {
    is.rgszComment++;
    fprintf(file, "%s%s\n", us.fWriteOld ? "" : "; ", is.rgszComment[1]);
  }
  fclose(file);
  return fTrue;
}


/*
******************************************************************************
** User Input Routines.
******************************************************************************
*/

/* Given a string, return an index number corresponding to what the string */
/* indicates, based on a given parsing mode. In most cases this is mainly  */
/* looking up a string in the appropriate array and returning the index.   */

int NParseSz(szEntry, pm)
byte *szEntry;
int pm;
{
  byte szLocal[cchSzMax], *sz, ch0, ch1, ch2;
  int cch, n, i;

  /* First strip off any leading or trailing spaces. */
  for (cch = 0; szLocal[cch] = szEntry[cch]; cch++)
    ;
  while (cch && szLocal[cch-1] <= ' ')
    szLocal[--cch] = chNull;
  for (sz = szLocal; *sz && *sz <= ' '; sz++, cch--)
    ;

  if (cch >= 3) {
    ch0 = ChCap(sz[0]); ch1 = ChUncap(sz[1]); ch2 = ChUncap(sz[2]);
    switch (pm) {
    /* Parse months, e.g. "February" or "Feb" -> 2 for February. */
    case pmMon:
      for (i = 1; i <= cSign; i++) {
        if (ch0 == szMonth[i][0] && ch1 == szMonth[i][1] &&
          ch2 == szMonth[i][2])
          return i;
      }
      break;
    /* Parse planets, e.g. "Jupiter" or "Jup" -> 6 for Jupiter. */
    case pmObject:
      for (i = 1; i <= cObj; i++) {
        if (ch0 == szObjName[i][0] && ch1 == szObjName[i][1] &&
          ch2 == szObjName[i][2])
          return i;
      }
      if (ch0 == 'L' && ch1 == 'i' && ch2 == 'l')
        return oLil;
      if (ch0 == 'S' && ch1 == '.' && ch2 == 'n')
        return oSou;
      break;
    /* Parse aspects, e.g. "Conjunct" or "Con" -> 1 for the Conjunction. */
    case pmAspect:
      for (i = 1; i <= cAspect; i++) {
        if (ch0 == szAspectAbbrev[i][0] &&
          ch1 == (byte)ChUncap(szAspectAbbrev[i][1]) &&
          ch2 == szAspectAbbrev[i][2])
          return i;
      }
      break;
    /* Parse house systems, e.g. "Koch" or "Koc" -> 1 for Koch houses. */
    case pmSystem:
      for (i = 1; i <= cSystem; i++) {
        if (ch0 == szSystem[i][0] && ch1 == szSystem[i][1] &&
          ch2 == szSystem[i][2])
          return i;
      }
    /* Parse zodiac signs, e.g. "Scorpio" or "Sco" -> 8 for Scorpio. */
    case pmSign:
      for (i = 1; i <= cSign; i++) {
        if (ch0 == szSignName[i][0] && ch1 == szSignName[i][1] &&
          ch2 == szSignName[i][2])
          return i;
      }
    /* Parse colors, e.g. "White" or "Whi" -> 15 for White. */
    case pmColor:
      for (i = 0; i < cColor; i++) {
        if (ch0 == szColor[i][0] && ch1 == szColor[i][1] &&
          ch2 == (byte)ChUncap(szColor[i][2]))
          return i;
      }
    }
  }
  n = atoi(sz);

  if (pm == pmYea) {
    /* For years, process any "BC" (or "B.C.", "b.c", and variations) and   */
    /* convert an example such as "5BC" to -4. For negative years, note the */
    /* difference of one, as 1AD was preceeded by 1BC, with no year zero.   */
    i = Max(cch-1, 0);
    if (i && sz[i] == '.')
      i--;
    if (i && ChCap(sz[i]) == 'C')
      i--;
    if (i && sz[i] == '.')
      i--;
    if (i && ChCap(sz[i]) == 'B')
      n = 1 - n;
  }
  return n;
}


/* Given a string, return a floating point number corresponding to what the  */
/* string indicates, based on a given parsing mode, like above for integers. */

real RParseSz(szEntry, pm)
byte *szEntry;
int pm;
{
  byte szLocal[cchSzMax], *sz, *pch, ch, chdot, minutes[12];
  int cch, havedot, dot1, dot2, newstyle = fFalse, i, j, f = fFalse;
  real r, rMinutes, rSeconds;

  /* First strip off any leading or trailing spaces. */
  for (cch = 0; szLocal[cch] = szEntry[cch]; cch++)
    ;
  while (cch && szLocal[cch-1] <= ' ')
    szLocal[--cch] = chNull;
  for (sz = szLocal; *sz && *sz <= ' '; sz++, cch--);
    ;
  /* Capitalize all letters and make colons be periods to be like numbers. */
  for (pch = sz; *pch; pch++) {
    ch = *pch;
    if (ch == ':')
      ch = '.';
    else
      ch = ChCap(ch);
    *pch = ch;
  }
  ch = sz[0];

  if (pm == pmTim) {
    /* For times, process "Noon" and "Midnight" (or just "N" and "M"). */
    if (ch == 'N')
      return 12.0;
    else if (ch == 'M')
      return 0.0;
  } else if (pm == pmDst) {
    /* For the Daylight time flag, "Daylight", "Yes", and "True" (or just */
    /* their first characters) are all indications to be ahead one hour.  */
    if (ch == 'D' || ch == 'Y' || ch == 'T')
      return 1.0;
    /* "Standard", "No", and "False" mean the normal zero offset. */
    else if (ch == 'S' || ch == 'N' || ch == 'F')
      return 0.0;
  } else if (pm == pmZon) {
    /* For time zones, see if the abbrev is in a table, e.g. "EST" -> 5. */
    for (i = 0; i < cZone; i++)
      if (NCompareSz(sz, szZon[i]) == 0)
        return rZon[i];
  } else if (pm == pmLon || pm == pmLat) {
    /* For locations, negate the value for an "E" or "S" in the middle    */
    /* somewhere (e.g. "105E30" or "27:40S") for eastern/southern values. */
    for (i = 0; i < cch; i++) {
      ch = sz[i];
      if (FCapCh(ch)) {
        if (ch == 'E' || ch == 'S')
          f = fTrue;
        sz[i] = '.';
        i = cch;
      }
    }
    ch = sz[0];
  }

/* In new time and locations strings there are at least two dots now,    */
/* so we have to locate, if this string has second dot. If not, it's old */
/* style string. But some old style strings can have second dot at end,  */
/* so we have to distinguish them from new strings with two dots. VA.    */

  newstyle = fTrue;
  if (pm == pmTim || pm == pmLon || pm == pmLat) {
    havedot = 0; dot1 = 0; dot2 = 0;
    for (i = 0; i < cch; i++) {
      chdot = sz[i];
      if (chdot == '.') {
        if (havedot) {
          dot2 = i;
          i = cch;
        } else {
          dot1 = i;
          havedot = 1;
        }
      }
    }
    if (dot2 == 0 || dot2 == cch -1)
      newstyle = fFalse;

/* Now, when we know that it is new style string, we have to convert */
/* it to the old style.                                              */

    if (newstyle) {
      for (i = dot1+1; i < cch; i++) {
        j = i - (dot1 + 1);
        if (sz[i] >= '.' && sz[i] <= '9' && sz[i] != '/')
          minutes[j] = sz[i];
/*        if (minutes[j] == chNull || j > 9)  */
        else
          i = cch;
      }
      rMinutes = atof(minutes);
      rSeconds = RFract(rMinutes) / 0.6;
      if (rSeconds >= 1.0)
        return rLarge;
      sprintf (minutes, "%6.4f", rSeconds);
      for (i = 2; i < 5; i++) {
        j = i - 2 + dot2;
        sz[j] = minutes[i];
      }
    }
  }

  /* Anything still at this point should be in a numeric format. */
  if (!FNumCh(ch) && ch != '+' && ch != '-' && ch != '.')
    return rLarge;
  r = (f ? -1.0 : 1.0) * atof(sz);

  if (pm == pmTim) {
    /* Backtrack over any time suffix, e.g. "AM", "p.m." and variations. */
    i = Max(cch-1, 0);
    if (i && sz[i] == '.')
      i--;
    if (i && sz[i] == 'M')
      i--;
    if (i && sz[i] == '.')
      i--;
    if (i) {
      ch = sz[i];
      if (ch == 'A')                   /* Adjust value appropriately */
        r = r >= 12.0 ? r-12.0 : r;    /* if AM or PM suffix.        */
      else if (ch == 'P')
        r = r >= 12.0 ? r : r+12.0;
    }
  }
  return r;
}


/* Stop and wait for the user to enter a line of text given a prompt to */
/* display and a string buffer to fill with it.                         */

void InputString(szPrompt, sz)
byte *szPrompt, *sz;
{
  FILE *file;
  int cch;

  file = is.S; is.S = stdout;
  PrintSz(szPrompt);
  AnsiColor(kYellow);
  PrintSz(" > ");
  AnsiColor(kDefault);
  if (fgets(sz, cchSzMax, stdin) == NULL)  /* Pressing control-D terminates */
    Terminate(tcForce);                    /* the program on some machines. */
  cch = CchSz(sz);
  while (cch > 0 && sz[cch-1] < ' ')
    cch--;
  sz[cch] = chNull;
  is.S = file;
  is.cchCol = 0;
}


/* Prompt the user for a floating point value, parsing as appropriate, and */
/* make sure it conforms to the specified bounds before returning it.      */

int NInputRange(szPrompt, low, high, pm)
byte *szPrompt;
int low, high;
int pm;
{
  byte szLine[cchSzDef];
  int n;

  loop {
    InputString(szPrompt, szLine);
    n = NParseSz(szLine, pm);
    if (FBetween(n, low, high))
      return n;
    sprintf(szLine, "Value %d out of range from %d to %d.", n, low, high);
    PrintWarning(szLine);
  }
}


/* This is identical to above except it takes/returns floating point values. */

real RInputRange(szPrompt, low, high, pm)
byte *szPrompt;
real low, high;
int pm;
{
  byte szLine[cchSzDef];
  real r;

  loop {
    InputString(szPrompt, szLine);
    r = RParseSz(szLine, pm);
    if (FBetween(r, low, high))
      return r;
    sprintf(szLine, "Value %.0f out of range from %.0f to %.0f.",
      r, low, high);
    PrintWarning(szLine);
  }
}


/* This important procedure gets all the parameters defining the chart that  */
/* will be worked with later. Given a "filename", it gets from it all the    */
/* pertinent chart information. This is more than just reading from a file - */
/* the procedure also takes care of the cases of prompting the user for the  */
/* information and using the time functions to determine the date now - the  */
/* program considers these cases "virtual" files. Furthermore, when reading  */
/* from a real file, we have to check if it was written in the -o0 format.   */

bool FInputData(szFile)
byte *szFile;
{
  FILE *file;
  byte sz[cchSzDef], ch;
  int i, fT;
  real k, l, m;

  /* If we are to read from the virtual file "nul" that means to leave the */
  /* chart information alone with whatever settings it may have already.   */

  if (NCompareSz(szFile, szNulCore) == 0) {
    is.fHaveInfo = fTrue;
    return fTrue;
  }

  /* If we are to read from the virtual file "set" then that means use a   */
  /* particular set of chart information generated earlier in the program. */

  if (NCompareSz(szFile, szSetCore) == 0) {
    is.fHaveInfo = fTrue;
    ciCore = ciSave;
    return fTrue;
  }

#ifdef TIME
  /* If we are to read from the file "now" then that means use the time */
  /* functions to calculate the present date and time.                  */

  if (NCompareSz(szFile, szNowCore) == 0) {
    is.fHaveInfo = fTrue;
    SS = us.dstDef; ZZ = us.zonDef; OO = us.lonDef; AA = us.latDef;
    GetTimeNow(&MM, &DD, &YY, &TT, ZZ-SS);
    ciCore.nam = ciCore.loc = "";
    return fTrue;
  }
#endif

#ifndef WIN
  /* If we are to read from the file "tty" then that means prompt the user */
  /* for all the chart information.                                        */

  if (NCompareSz(szFile, szTtyCore) == 0) {
    file = is.S; is.S = stdout;
    if (!us.fNoSwitches) {
      /* Temporarily disable an internal redirection of output to a file  */
      /* because we always want user headers and prompts to be displayed. */

      AnsiColor(kWhite);
      sprintf(sz, "** %s version %s ", szAppName, szVersionCore); PrintSz(sz);
      sprintf(sz, "(See '%cHc' switch for copyrights and credits.) **\n",
        chSwitch); PrintSz(sz);
      AnsiColor(kDefault);
      sprintf(sz, "   Invoke as '%s %cH' for list of command line options.\n",
        ProcessProgname(is.szProgName), chSwitch); PrintSz(sz);
    }

    MM = NInputRange("Enter month for chart (e.g. '8' 'Aug')",
      1, 12, pmMon);
    DD = NInputRange("Enter day   for chart (e.g. '1' '31') ",
      1, DayInMonth(MM, 0), pmDay);
    YY = NInputRange("Enter year  for chart (e.g. '1995')   ",
      -5000, 5000, pmYea);
    if (FBetween(YY, 0, 99)) {
      sprintf(sz,
        "Assuming first century A.D. is really meant instead of %d.",
        1900 + YY);
      PrintWarning(sz);
    }
    TT = RInputRange("Enter time  for chart (e.g. '18:30' '6:30pm')  ",
      -2.0, 24.0, pmTim);
    SS = us.fWriteOld ? 0.0 :
      RInputRange("Enter if Daylight time in effect (e.g. 'y' '1')",
      -24.0, 24.0, pmDst);
    ZZ = RInputRange("Enter time zone (e.g. '5' 'ET' for Eastern)    ",
      -24.0, 24.0, pmZon);
    if ((int)(RFract(ZZ) * 100.0 + rRound) == 50) {
      PrintWarning(
        "Assuming unusual zone of 50 minutes after the hour instead of 30.");
    }
    OO = RInputRange("Enter Longitude of place (e.g. '122W20')",
      -rDegHalf, rDegHalf, pmLon);
    AA = RInputRange("Enter Latitude  of place (e.g. '47N36') ",
      -rDegQuad, rDegQuad, pmLat);
    if (!us.fWriteOld) {
      InputString("Enter name or title for chart ", sz);
      ciCore.nam = SzPersist(sz);
      InputString("Enter name of city or location", sz);
      ciCore.loc = SzPersist(sz);
    }
    PrintL();
    is.cchRow = 0;
    is.S = file;
    return fTrue;
  }
#endif /* WIN */

  /* Now that the special cases are taken care of, we can assume we are */
  /* to read from a real file.                                          */

  file = FileOpen(szFile, 1);
  if (file == NULL)
    return fFalse;
  is.fHaveInfo = fTrue;
  ch = getc(file); ungetc(ch, file);

  /* Read the chart parameters from a standard command switch file. */

  if (ch == '@') {
    fT = is.fSzPersist; is.fSzPersist = fFalse;
    if (!FProcessSwitchFile(szFile, file))
      return fFalse;
    is.fSzPersist = fT;

  /* Read the chart info from an older style -o list of seven numbers. */

  } else if (FNumCh(ch)) {
    SS = 0.0;
    fscanf(file, "%d%d%d", &MM, &DD, &YY);
    fscanf(file, "%lf%lf%lf%lf", &TT, &ZZ, &OO, &AA);
    if (!FValidMon(MM) || !FValidDay(DD, MM, YY) || !FValidYea(YY) ||
      !FValidTim(TT) || !FValidZon(ZZ) || !FValidLon(OO) || !FValidLat(AA)) {
      PrintWarning("Values in old style chart info file are out of range.");
      return fFalse;
    }

  /* Read the actual chart positions from a file produced with the -o0. */

  } else if (ch == 'S') {
    MM = -1;

    /* Hack: A negative month value means the chart parameters are invalid, */
    /* hence -o0 is in effect and we can assume the chart positions are     */
    /* already in memory so we don't have to calculate them later.          */

    for (i = 1; i <= oNorm; i++) {
      fscanf(file, "%s%lf%lf%lf", sz, &k, &l, &m);
      planet[i] = Mod((l-1.0)*30.0+k+m/60.0);
      fscanf(file, "%s%lf%lf", sz, &k, &l);
      if ((m = k+l/60.0) > rDegHalf)
        m = rDegMax - m;
      planetalt[i] = m;
      ret[i] = RFromD(sz[1] == 'D' ? 1.0 : -1.0);

      /* -o0 files from versions 3.05 and before don't have the uranians in  */
      /* them. Be prepared to skip over them in old files for compatibility. */

      if (i == oVtx) {
        while (getc(file) >= ' ')
          ;
        if ((ch = getc(file)) != 'H')
          i = cuspHi;
        else
          i = cObj;
      }
      if (i == oNod)
        i = oFor-1;
      else if (i == oFor)
        i = oLil-1;
      else if (i == oLil)
        i = oEP -1;
      else if (i == oEP)
        i = oVtx-1;
    }
    for (i = 1; i <= cSign/2; i++) {
      fscanf(file, "%s%lf%lf%lf", sz, &k, &l, &m);
      chouse[i+6] = Mod((chouse[i] = Mod((l-1.0)*30.0+k+m/60.0))+rDegHalf);
    }
    for (i = 1; i <= cSign; i++)
      planet[cuspLo-1+i] = chouse[i];
    planet[oMC] = planet[oLil]; planet[oNad] = Mod(planet[oMC]  + rDegHalf);
    planet[oAsc] = planet[oEP]; planet[oDes] = Mod(planet[oAsc] + rDegHalf);
    planet[oSou] = Mod(planet[oNod] + rDegHalf); ret[oSou] = ret[oNod];

  } else {
    sprintf(sz,
      "The chart info file is not in any valid format (character %d).",
      (int)ch);
    PrintWarning(sz);
    return fFalse;
  }
  fclose(file);
  return fTrue;
}


   /* Look for file determined in variable szFileNameSearch in different  */
   /* directories, used by Astrolog. If find file, add szWcommand before  */
   /* path to file and return result in szFilePathWin. Used in Windows    */
   /* version Help, also to check, if exists stars data file fixstars.ast */

bool FileFind(szWcommand)
byte *szWcommand;
{
  byte name[cchSzMax], mode[3] = "r";
  FILE *file;
#ifdef ENVIRON
  byte *env;
#endif

  /* First look for the file in the current directory. */

  file = fopen(szFileNameSearch, mode);
  if (file != NULL) {
    fclose(file);
    strcpy(szFilePathWin, szWcommand);
    strcat(szFilePathWin, szFileNameSearch);
    return fTrue;
  }

#ifdef ENVIRON

  /* Next look for the file in the directory indicated by the version */
  /* specific system environment variable.                            */
  sprintf(name, "%s%s", ENVIRONVER, szVersionCore);
  env = getenv(name);
  if (env && *env) {
    sprintf(name, "%s%c%s", env, chDirSep, szFileNameSearch);
    file = fopen(name, mode);
    if (file != NULL) {
      fclose(file);
      goto PrepLine;
    }
  }

  /* Next look in the directory in the general environment variable. */
  env = getenv(ENVIRONALL);
  if (env && *env) {
    sprintf(name, "%s%c%s", env, chDirSep, szFileNameSearch);
    file = fopen(name, mode);
    if (file != NULL) {
      fclose(file);
      goto PrepLine;
    }
  }

  /* Next look in the directory in the version prefix environment variable. */
  env = getenv(ENVIRONVER);
  if (env && *env) {
    sprintf(name, "%s%c%s", env, chDirSep, szFileNameSearch);
    file = fopen(name, mode);
    if (file != NULL) {
      fclose(file);
      goto PrepLine;
    }
  }
#endif

  /* Finally look in directory DEFAULT_DIR, defined at compile time. */

  sprintf(name, "%s%c%s", DEFAULT_DIR, chDirSep, szFileNameSearch);
  file = fopen(name, mode);
  if (file != NULL) {
    fclose(file);
    goto PrepLine;
  }
  return fFalse;
PrepLine:
  strcpy(szFilePathWin, szWcommand);
  strcat(szFilePathWin, name);
  return fTrue;
}

/* io.c */
