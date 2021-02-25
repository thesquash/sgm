# SGM:  The STLWRT-ian GTK Modules
## GTK Modules of all kinds, for a classic GTK+ 2-esque user interface

SGM is a collection of useful modules for GTK, mostly to restore a more
classic user interface and experience to GTK+ 3 and above.  Currently,
this repository only contains the code for the "sgm-flexible-mnemonics"
module, but more are planned to follow.  Similarly, this module is known
not to work with GTK 4 yet, but support for GTK 4 should come eventually
too, as long as the community doesn't drag their feet in adopting GTK 4
(but that's a different story).

### sgm-flexible-mnemonics

*Mnemonics* are the underlined portions of text which indicate which key to
press to activate a particular widget, be it a menu item or a button.
Prior to GTK+ 3.9.8, a setting called `gtk-auto-mnemonics` could be modified
to either always display these underlines, or display these underlines only
when the "modifier key" (typically Alt on many keyboards) was pressed.  In
GTK+ 3.9.8, the latter mode is always used no matter the setting of
`gtk-auto-mnemonics`.  This module restores the classic mnemonic behavior to
GTK+ 3.9.8 and later versions of GTK.

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

### Building the code

Building the code couldn't be much easier.  You just need:

 - Meson
 - Ninja
 - GTK: currently only version 3.8 or later will suffice, not version 4.

To build the modules in this package:

 1. Clone this repository, or obtain a source tarball of this repository and
    extract the tarball.

 2. Change directory into the location where your copy of the code is stored.

 3. Make a build directory, then change directory into that:
        mkdir .build; cd .build

 4. Run the setup:
        meson ..

 5. Compile the code:
        ninja

 6. Install the modules:
        sudo ninja install

To actually use the modules, you'll need to inform GTK about their existence
and, more importantly, that you want to use them.  On GTK+ 3 you can create
a file `~/.config/gtk-3.0/settings.ini` that contains:

        [Settings]
        gtk-modules = [list of modules separated by colons]

Do *not* surround the list of modules with quotes!  This has unintended side
effects including presentation of cryptic `Gtk-Message`s about failing to
find module *x* or *y*.

On GTK 4, use the same method as on GTK+ 3, but change the `gtk-3.0` above to
`gtk-4.0`.

On GTK+ 2 (few modules here are useful for GTK+ 2), create a file
`~/.config/gtk-2.0/gtkrc` which contains the following:

        gtk-modules = [quoted list of modules separated by colons]

It is important to *surround the list of modules with double quotes on GTK+ 2*.
Otherwise, the modules will not load.  Yes, it's inconsistent.  But it's not
my fault.

***

Thanks for checking out (pun intended) this repository!
