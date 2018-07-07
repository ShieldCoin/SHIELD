#!/bin/bash

export LC_ALL=C
TOPDIR=${TOPDIR:-$(git rev-parse --show-toplevel)}
BUILDDIR=${BUILDDIR:-$TOPDIR}

BINDIR=${BINDIR:-$BUILDDIR/src}
MANDIR=${MANDIR:-$TOPDIR/doc/man}

SHIELDD=${SHIELDD:-$BINDIR/shieldd}
SHIELDCLI=${SHIELDCLI:-$BINDIR/shield-cli}
SHIELDTX=${SHIELDTX:-$BINDIR/shield-tx}
SHIELDQT=${SHIELDQT:-$BINDIR/qt/shield-qt}

[ ! -x $SHIELDD ] && echo "$shieldd not found or not executable." && exit 1

# The autodetected version git tag can screw up manpage output a little bit
XSHVER=($($SHIELDCLI --version | head -n1 | awk -F'[ -]' '{ print $6, $7 }'))

# Create a footer file with copyright content.
# This gets autodetected fine for shieldd if --version-string is not set,
# but has different outcomes for shield-qt and shield-cli.
echo "[COPYRIGHT]" > footer.h2m
$shieldd --version | sed -n '1!p' >> footer.h2m

for cmd in $shieldd $SHIELDCLI $SHIELDTX $SHIELDQT; do
  cmdname="${cmd##*/}"
  help2man -N --version-string=${XSHVER[0]} --include=footer.h2m -o ${MANDIR}/${cmdname}.1 ${cmd}
  sed -i "s/\\\-${XSHVER[1]}//g" ${MANDIR}/${cmdname}.1
done

rm -f footer.h2m
