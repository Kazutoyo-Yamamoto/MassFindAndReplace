========================================================================
    CONSOLE APPLICATION : Mass Find and Replace
========================================================================

ABOUT:

Mass Find and Replace for finding and replacing multiple items.

Program was designed for replacing names in an inventory for
	games, namely translating names, with out having to do it manually.

The program is perticularly useful for finding and replacing english words
	as all english words are generally delimited by a space.

HOW TO USE:
Open console with the input text, find text, and replace text in the same folder
Enter the command
MassFindAndReplace.exe Input.txt Find.txt Replace.txt
When program is done it will create an Output.txt with the changes applied

Example:

Input.txt:
===============================
Name: ダガー
Attack: 9
Craft: 鉄鉱石

Name: ショートソード
Attack: 15
Craft: ダガー, 鉄鉱石
===============================

Find.txt:
===============================
ダガー
鉄鉱石
ショートソード
===============================

Replace.txt:
===============================
Dagger
Iron Ore
Shortsword
===============================

Output.txt:
===============================
Name: Dagger
Attack: 9
Craft: Iron Ore

Name: Shortsword
Attack: 15
Craft: Dagger, Iron Ore
===============================

Copyright 2019 Kazutoyo Yamamoto