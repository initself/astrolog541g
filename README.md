# Astrolog 5.41g

## Astrolog 5.30 to 5.40    
Walter D. Pullen (Astara@msn.com) wrote the original version of Astrolog. He ported the main planetary calculation routines to C. These routines were based on the work of James Neely. Neely's routines were listed in Michael Erlewine's Manual of Computer Programming for Astrologers. The program was originally written in 16 bit.

Over time, several people began writing upgraded versions of Astrolog. Walter Pullen wrote Astrolog 5.30. He borrowed the accurate ephemeris databases and formulae in the calculation routines found in the Placalc program. These were written and copyrighted by Alois Treindl and Astrodienst AG. Valja (Valentin Abramov) modified Astrolog 5.30, creating successive versions from 5.30a to 5.30g, including the last of this series, 5.30g1.

Alois Treindl then modified 5.30 to include the new Swiss Ephemeris instead of the older Placalc ephemeris, calling this 5.31. Valja included this new modification and changed the name from 5.30g1 to 5.31g.

Walter Pullen then wrote the next version of Astrolog, version 5.40, using the older Placalc ephemeris. You can download a copy of Astrolog 5.40 and auxiliary files at the Astrolog webpage at Bonnie's Links. Tyrin Price has written a miniFAQ for Astrolog 5.40; you can find it at Astrologica.

Astrolog 5.30, 5.30a to 5.30g1, and 5.40 all use the Placalc ephemeris. They look for ephemeris files in the folder that contains the astrolog.exe file. There are three types of files: CHI_##, CPJV_##, and LRZ5_##. The CHI files contain the positions of Chiron, the CHJV files contain the positions of the four main asteroids, and the LRZ5 files contain the positions of Jupiter through Pluto.

In Astrolog 5.40, the ephemeris files can be turned on and off by going to Setting -> Calculation Settings. When the ephemeris files are turned off, Astrolog 5.40 will use the Matrix routines which give locations significantly in error the further we go away from the 20th century. If the ephemeris files are turned on but can't be found, these versions of Astrolog will return an error message and use the Matrix routines. Astrolog 5.31 and 5.31g use the Swiss Ephemeris. The Swiss Ephemeris is discussed in the next section.

Astrolog 5.40 supports the YE switch which is used to modify the orbital characteristics of any selected planet. This flag can be used to "add" a new (hypothetical) planet to Astrolog 5.40. See Inserting Transpluto into Astrolog 5.4 Using the YE Switch for a full discussion of entering hypothetical planets into Astrolog 5.4.

## Astrolog 5.41 to 5.41G

Alois Treindl followed up Walter Pullen's version 5.40 with version 5.41. This version uses the new Swiss Ephemeris which is faster and more precise than the Placalc ephemeris. This version also included the addition of fixed stars, improved graphics, and a new method for interpretations.

Valja then took 5.41 and included all the changes he had made up to 5.31g, calling it 5.41a. He then wrote successive versions 5.41B, 5.41C, 5.41D, 5.41E, 5.41F and 5.41G. These are all 16-bit versions of Astrolog. They will not read the Placalc ephemeris files in the form of CHI_##, CPJV_##, and LRZ5_## which prior versions of Astrolog used. You can download a copy of Astrolog 5.41G at Astrologica.

These versions of Astrolog should use ephemeris files which can be downloaded from the Astrodienst website at: ftp://ftp.astro.com/pub/swisseph/ephe/. There are 3 types of Swiss Ephemeris files. Those of the form sepl_##.se1 are for the planets, semo_##.se1 are for the moon, and seas_##.se1 are for the asteroids. Each file covers 600 years, with the two digits in the file name (##) being the first two digits of the first year in the file. For example semo_18.se1 is the ephemeris file for the moon which covers the years 1800 to 2399. For files covering years that are BC, the "_" is replaced with an "m". The files can be downloaded for the time period that you need.

By default, versions such as Astrolog 5.41G look for the ephemeris files in the folder which contains the astrolog.exe file. The use of the ephemeris files can be turned on and off by going to Setting -> Calculation Settings. Like Astrolog 5.40, Astrolog 5.41G will also use the Matrix routines when the ephemeris files are turned off. This will give locations significantly in error the further we go away from the 20th century.

When the ephemeris files are turned on in Astrolog 5.41G but it can't find the ephemeris files, it will use a built-in analytical ephemeris which does provide very good precision. It appears that this built-in analytical ephemeris is provided by Swiss Ephemeris which quotes accuracy of "0.1 arc seconds for the planets and 3" for the Moon." No time period is given for this accuracy to be relevant over, however the built-in ephemeris is valid for 3000BC to 3000AD.

For the majority of purposes, this accuracy is quite acceptable. Unfortunately, this built-in analytical ephemeris does not include the asteroids, only the moon and planets. If Astrolog 5.41G can't find the asteroid ephemeris files, then it will use the rather inaccurate Matrix routines for asteroids such as Chiron.

Astrolog 5.41G also supports the YE switch which is used to modify the orbital characteristics of any selected planet. This flag can be used to "add" a new (hypothetical) planet to Astrolog 5.40. See Inserting Transpluto into Astrolog 5.4 Using the YE Switch for a full discussion of entering hypothetical planets into Astrolog 5.4.
