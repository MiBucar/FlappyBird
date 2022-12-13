#pragma once

namespace obj {
	enum PlayerTextures {
		FLYING,
		FALLING,
		EMPTYPLY
	};

	enum BackgroundTextures {
		GAMEPLAY,
		MENU,
		EMPTYBCKG
	};

	enum Buttons {
		BTNPLAY,
		BTNPLAY_AGAIN,
		BTNHOME,
		BTNSCORE,
		BTNSETTINGS,
		BTNRESETSCORE,
		BTNRIGHTVOLUME,
		BTNLEFTVOLUME,
		EMPTYBTN
	};

	enum Files {
		FILESCORES,
		FILESAUDIO,
		EMPTYFILE
	};

	enum Text {
		TEXTSCOREGMP,
		TEXTSCOREDS,
		TEXTBEST,
		TEXT1,
		TEXT2,
		TEXT3,
		TEXT4,
		TEXT5,
		EMPTYTEXT
	};

	enum Screens {
		SCRDEATH,
		SCRSCORES,
		SCRSETTINGS,
		EMPTYSCR
	};

	enum Sound {
		SOUNDBUTTON,
		EMPTYSOUND
	};

	enum Music {
		MUSICGAME,
		EMPTYMUSIC
	};
}
