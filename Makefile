.PHONY: build

build:
	gcc src/*.c -o build/doc -lncursesw
clean:
	rm build/doc
run:
	gcc src/*.c -o build/doc -lncursesw
	build/doc
install: build
	install -Dm755 build/doc /usr/bin/sdoc
	printf '#sdoc\nI used ai to write this document lmao\n\n\0330sdoc is a small terminal documentation pager.\0330\n\nIt reads documentation installed under:\n\n    /usr/share/sdoc/\n\n\0331USAGE\0331\n\nRun sdoc with the path to a document relative to /usr/share/sdoc/:\n\n    sdoc sdoc/example\n\n\0332NAVIGATION\0332\n\nUse the following keys while viewing a document:\n\n    \0333Down Arrow\0333    Scroll down by one page\n    \0333Up Arrow\0333      Return to the previous page\n    \0333q\0333             Quit sdoc\n\nsdoc remembers previous page positions so that scrolling upward\nreturns to the exact location of the previous page.\n\n\0334DOCUMENT FORMAT\0334\n\nsdoc documents are primarily plain text. They may also contain\nformatting sequences.\n\nA formatting sequence consists of the ESC byte followed by a\ncolor code:\n\n    ESC 0    Cyan\n    ESC 1    Yellow\n    ESC 2    Green\n    ESC 3    Magenta\n    ESC 4    Red\n\nThe same sequence is used again to turn that color off.\n\nFor example:\n\n    ESC 0\n    This text is cyan.\n    ESC 0\n    This text is normal again.\n\n\0330The formatting sequences are consumed by sdoc and are not\nshown as part of the document.\0330\n\n\0331INSTALLATION\0331\n\nDocumentation intended for sdoc should be installed below:\n\n    /usr/share/sdoc/\n\nFor example:\n\n    /usr/share/sdoc/mypackage/example\n\ncan be opened with:\n\n    sdoc mypackage/example\n\n\0332DESIGN\0332\n\nsdoc is intentionally small. Documents are loaded into memory\nand rendered directly in a terminal using ncurses.\n\nThe document format is separate from terminal ANSI escape\nsequences. Authors therefore do not need to write terminal-\nspecific control sequences into their documentation.\n\n\0333CURRENT FEATURES\0333\n\n    Plain-text documents\n    Five foreground colors\n    Page-based scrolling\n    Previous-page history\n    ncurses terminal rendering\n\n\0334CURRENT LIMITATIONS\0334\n\n    No bold text\n    No images\n    No hyperlinks\n    No complex markup\n    No automatic document indexing\n\nThe goal is to keep sdoc small while still providing enough\nformatting to make technical documentation easy to read.\n' | sudo tee /usr/share/sdoc/sdoc/about > /dev/null
	sdoc sdoc/about
