# SGM:  The STLWRT-ian GTK Modules
## GTK Modules of all kinds, for a classic GTK+ 2-esque user interface

SGM is a collection of useful modules for GTK, mostly to restore a more
classic user interface and experience to GTK+ 3 and above.  Currently,
this repository only contains the code for the "sgm-flexible-mnemonics"
module, but more are planned to follow.  Similarly, this module is known
not to work with GTK 4 yet, but support for GTK 4 should come eventually
too, as long as the community doesn't drag their feet in adopting GTK 4
but that's a different story).

### sgm-flexible-mnemonics

*Mnemonics* are the underlined portions of text which indicate which key to
press to activate a particular widget, be it a menu item or a button.
Prior to GTK+ 3.9.8, a setting called `gtk-auto-mnemonics` could be modified
to either always display these underlines, or display these underlines only
when the "modifier key" (typically Alt on many keyboards) was pressed.  In
GTK+ 3.9.8, the latter mode is always used no matter the setting of
`gtk-auto-mnemonics`.  This module restores the classic mnemonic behavior to
GTK+ 3.9.8 and later versions of GTK.

### sgm-overlay-scrolling **(COMING SOON)**

Traditionally, scrollbars have appeared to the side of scrolled content.
In GTK+ 3.15.0, a new means of displaying scrollbars was introduced:
*overlay scrolling*.  When overlay scrolling is enabled, scrollbars do not
initially appear; instead they wait for mouse movement before appearing,
and even then appear *on top* of scrolled content instead of *to the side*
of said content.  This is good for users with little screen space, and it
would be tolerable to other users if there were an easy way to disable it;
however, until GTK+ 3.24.9 there was only an environment variable to
disable overlay scrolling globally.  An environment variable is tolerable,
but it needs to be set every time a GTK application is run, or else overlay
scrolling will be enabled again.  In GTK+ 3.24.9, a new setting was
introduced to disable overlay scrolling globally, `gtk-overlay-scrolling`.
But this setting left users of older versions of GTK in the lurch; even
today, some users continue to use GTK versions as old as 3.18 because that
is the latest version shipped by their distributor for an old Long Term
Support release of their distribution.  This module adds the
`gtk-overlay-scrolling` setting to GTK versions prior to 3.24.9, so that
conservative themes can universally set the `gtk-overlay-scrolling`
property to `false` to disable overlay scrolling -- even on GTK versions
prior to 3.24.9.

I created this module not so much because doing so is a necessity; it
is mostly because I admittedly have a big, fat mouth and told a friend of
mine that I could write a module for this.  But it's also good to have a
module that brings the GTK+ 3.24.9-and-later behavior to older versions
of GTK, I suppose.  Either way, my fat mouth has cost me and you're seeing
the fruits of my embarassing talkativeness.  But that's enough on the
topic of my fat mouth.

### Planned modules for the future

 * A "GTK Inspector"-like tool for GTK+ 2 would be quite cool and useful.
   Better yet, it doesn't need to be loaded all the time -- just when you
   think you'll need to debug a GTK program!

 * A module to add scrollbar stepper buttons to the ends of scrollbars on
   GTK 4 is in the works.  I actually have it working, I just need to
   commit it to this repository and clean it up a little.

If you have any further ideas on what you want in GTK, please file an
issue on this repository!  Pull requests are also welcome.  If you
find an issue in one of these modules, please start an issue for that,
too.

***

Thanks for checking out (pun intended) this repository!
