#include "../include/nlohmann/json.hpp"
#include "../include/misc/obfuscate.h"

#ifdef RELEASE_MODE
#define OBFUSCATE(data) (char*)AY_OBFUSCATE(data)
#else
#define OBFUSCATE(data) data
#endif

enum Types {
	Body = 0,
	Mask = 1,
	Hair = 2,
	Cape = 3,
	Prop = 4,
	Misc = 5,
};

static nlohmann::json spell_buffs = nlohmann::json::parse(OBFUSCATE(R"(
	[
		{
			"id": 1097748727,
			"name": "Glow 15",
			"effect": "glow",
			"icons": "UiMiscStarCluster",
			"type": 5
		},
		{
			"id": 1750685908,
			"name": "Energy 2x",
			"effect": "energy_charge_mult",
			"icons": "UiMenuBuffFastCharge",
			"type": 5
		},
		{
			"id": 1860519737,
			"name": "Anti Gravity 0 5x",
			"effect": "gravity_mult",
			"icons": "UiMenuBuffAntiGravity",
			"type": 5
		},
		{
			"id": -705906186,
			"name": "Birthdayhat Krill",
			"effect": "birthdayhat",
			"icons": "UiOutfitHornBirthdayHat01",
			"type": 5
		},
		{
			"id": 1441565188,
			"name": "Candle Trick",
			"effect": "candle_trick",
			"icons": "UiMenuBuffCandle",
			"type": 5
		},
		{
			"id": 847145578,
			"name": "Cat Curse",
			"effect": "cat_curse",
			"icons": "UiMenuBuffCatCurse",
			"type": 5
		},
		{
			"id": 901504997,
			"name": "Crab Rock Trick",
			"effect": "crab_rock_trick",
			"icons": "UIMenuBuffCrabRock",
			"type": 5
		},
		{
			"id": -915747335,
			"name": "Dnd",
			"effect": "dnd",
			"icons": "UIEye",
			"type": 5
		},
		{
			"id": 383062578,
			"name": "Goo Drain 0 5x",
			"effect": "goo_drain_mult",
			"icons": "UiEmoteNoThanks",
			"type": 5
		},
		{
			"id": 891098028,
			"name": "Height Large 3x",
			"effect": "height_mult",
			"icons": "UiMenuBuffGrow",
			"type": 5
		},
		{
			"id": 1692428656,
			"name": "Height Small 3x",
			"effect": "height_mult",
			"icons": "UiMenuBuffChibi",
			"type": 5
		},
		{
			"id": -305102667,
			"name": "Height Small 3x Handhold",
			"effect": "height_mult",
			"icons": "UiMenuBuffChibi",
			"type": 5
		},
		{
			"id": -105193858,
			"name": "Outfit Body Gardener",
			"effect": "outfit_body",
			"icons": "UiOutfitBodyGardener",
			"type": 0
		},
		{
			"id": 483128979,
			"name": "Outfit Body Muralist",
			"effect": "outfit_body",
			"icons": "UiOutfitBodyDOF23Muralist",
			"type": 0
		},
		{
			"id": 782433094,
			"name": "Outfit Body Orangelove",
			"effect": "outfit_body",
			"icons": "UiOutfitBodyAP16OrangeLove",
			"type": 0
		},
		{
			"id": 1482655023,
			"name": "Outfit Body Rainbowtrousers",
			"effect": "outfit_body",
			"icons": "UiOutfitBodyRainbow",
			"type": 0
		},
		{
			"id": -1134828593,
			"name": "Outfit Body Runaway",
			"effect": "outfit_body",
			"icons": "UiOutfitBodyAP16SlateRunaway",
			"type": 0
		},
		{
			"id": -1535254839,
			"name": "Outfit Body Snowman",
			"effect": "outfit_body",
			"icons": "UiMenuBuffDOW22SnowmanBody",
			"type": 5
		},
		{
			"id": -495233219,
			"name": "Outfit Body Sword",
			"effect": "outfit_body",
			"icons": "UiOutfitBodyAP11Sword",
			"type": 0
		},
		{
			"id": 969946279,
			"name": "Outfit Body Witchbody",
			"effect": "outfit_body",
			"icons": "UiOutfitBodyWitch",
			"type": 0
		},
		{
			"id": 373243257,
			"name": "Outfit Hair Blossom",
			"effect": "outfit_hair",
			"icons": "UiOutfitHairBlossom",
			"type": 2
		},
		{
			"id": -1543558130,
			"name": "Outfit Hair Carp",
			"effect": "outfit_hair",
			"icons": "UiOutfitHairFish",
			"type": 2
		},
		{
			"id": -25012636,
			"name": "Outfit Hair Cathair",
			"effect": "outfit_hair",
			"icons": "UiOutfitHairDOM22Cat",
			"type": 2
		},
		{
			"id": -2099997114,
			"name": "Outfit Hair Doublebun",
			"effect": "outfit_hair",
			"icons": "UiOutfitHairDoubleBun",
			"type": 2
		},
		{
			"id": 2093744529,
			"name": "Outfit Hair Liondance",
			"effect": "outfit_hair",
			"icons": "UiOutfitHairLionDance",
			"type": 2
		},
		{
			"id": 1046521292,
			"name": "Outfit Hair Pumpkin",
			"effect": "outfit_hair",
			"icons": "UiOutfitHairAP04Pumpkin",
			"type": 2
		},
		{
			"id": -521490982,
			"name": "Outfit Hair Rainbowbeanie",
			"effect": "outfit_hair",
			"icons": "UiOutfitHairRainbowHat",
			"type": 2
		},
		{
			"id": 239584271,
			"name": "Outfit Hair Runaway",
			"effect": "outfit_hair",
			"icons": "UiOutfitHairAP16RunawayBob",
			"type": 2
		},
		{
			"id": 419537417,
			"name": "Outfit Hair Snowman",
			"effect": "outfit_hair",
			"icons": "UiMenuBuffDOW22SnowmanHead",
			"type": 5
		},
		{
			"id": -1760741911,
			"name": "Outfit Hair Spiderhair",
			"effect": "outfit_hair",
			"icons": "UiOutfitHairSpider",
			"type": 2
		},
		{
			"id": 1059767859,
			"name": "Outfit Hair Spintrick",
			"effect": "outfit_hair",
			"icons": "UiOutfitHairAP09MultiBuns",
			"type": 2
		},
		{
			"id": -2092825638,
			"name": "Outfit Hair Winterhat",
			"effect": "outfit_hair",
			"icons": "UiOutfitHairWinterHat",
			"type": 2
		},
		{
			"id": 116679863,
			"name": "Outfit Hair Witchhair",
			"effect": "outfit_hair",
			"icons": "UiOutfitHairWitch",
			"type": 2
		},
		{
			"id": 1983755432,
			"name": "Outfit Hair Witchhat",
			"effect": "outfit_hair",
			"icons": "UiOutfitHairWitchHat",
			"type": 2
		},
		{
			"id": -823266018,
			"name": "Outfit Hair Woolhat",
			"effect": "outfit_hair",
			"icons": "UiOutfitHairWoolHat",
			"type": 2
		},
		{
			"id": -1409683913,
			"name": "Outfit Hair Xmas",
			"effect": "outfit_hair",
			"icons": "UiOutfitHairSantaHat",
			"type": 2
		},
		{
			"id": -848739711,
			"name": "Outfit Horn Bunny",
			"effect": "outfit_horn",
			"icons": "UiOutfitHornBunny",
			"type": 5
		},
		{
			"id": 551055685,
			"name": "Outfit Horn Carp",
			"effect": "outfit_horn",
			"icons": "UiOutfitHornFish",
			"type": 5
		},
		{
			"id": -347711956,
			"name": "Outfit Horn Coral",
			"effect": "outfit_horn",
			"icons": "UiOutfitHornCoral",
			"type": 5
		},
		{
			"id": 942365523,
			"name": "Outfit Horn Flowercrown",
			"effect": "outfit_horn",
			"icons": "UiOutfitHornFlowerCrown",
			"type": 5
		},
		{
			"id": 2050094531,
			"name": "Outfit Horn Kizuna",
			"effect": "outfit_horn",
			"icons": "UiOutfitHornKizunaAi",
			"type": 5
		},
		{
			"id": -1989753674,
			"name": "Outfit Horn Moonstar",
			"effect": "outfit_horn",
			"icons": "UiOutfitHornAP16MoonStar",
			"type": 5
		},
		{
			"id": -1616733323,
			"name": "Outfit Horn Orange",
			"effect": "outfit_horn",
			"icons": "UiOutfitHornOrange",
			"type": 5
		},
		{
			"id": -1590289609,
			"name": "Outfit Horn Rainbowearring",
			"effect": "outfit_horn",
			"icons": "UiOutfitHornRainbowEarring",
			"type": 5
		},
		{
			"id": -1769208928,
			"name": "Outfit Horn Rainbowheadphones",
			"effect": "outfit_horn",
			"icons": "UiOutfitHornRainbowHeadphones",
			"type": 5
		},
		{
			"id": 2141511649,
			"name": "Outfit Horn Rainbowpoppy",
			"effect": "outfit_horn",
			"icons": "UiOutfitHornRainbowPoppy",
			"type": 5
		},
		{
			"id": -1014212311,
			"name": "Outfit Horn Rainbowpoppy2",
			"effect": "outfit_horn",
			"icons": "UiOutfitHornRainbowPoppy02",
			"type": 5
		},
		{
			"id": -290700605,
			"name": "Outfit Horn Rainbowtassel",
			"effect": "outfit_horn",
			"icons": "UiOutfitHornRainbowTassel",
			"type": 5
		},
		{
			"id": 1372838509,
			"name": "Outfit Horn Snowflake",
			"effect": "outfit_horn",
			"icons": "UiOutfitHornSnowflake",
			"type": 5
		},
		{
			"id": 2052387583,
			"name": "Outfit Horn Summerhat",
			"effect": "outfit_horn",
			"icons": "UiOutfitHornSummerHat",
			"type": 5
		},
		{
			"id": -171149928,
			"name": "Outfit Horn Summershell",
			"effect": "outfit_horn",
			"icons": "UiOutfitHornShell",
			"type": 5
		},
		{
			"id": -75786201,
			"name": "Outfit Horn Witchhat",
			"effect": "outfit_horn",
			"icons": "UiOutfitHornWitchHat",
			"type": 5
		},
		{
			"id": 1123843208,
			"name": "Outfit Horn Witheredhorn",
			"effect": "outfit_horn",
			"icons": "UiOutfitHornWithered",
			"type": 5
		},
		{
			"id": 1909998088,
			"name": "Outfit Horn Xmas",
			"effect": "outfit_horn",
			"icons": "UiOutfitHornElk",
			"type": 5
		},
		{
			"id": -218615327,
			"name": "Outfit Mask Actor",
			"effect": "outfit_mask",
			"icons": "UiOutfitMaskAP05Actor",
			"type": 1
		},
		{
			"id": -901640940,
			"name": "Outfit Mask Catmask",
			"effect": "outfit_mask",
			"icons": "UiOutfitMaskDOM22Cat",
			"type": 1
		},
		{
			"id": 371568737,
			"name": "Outfit Mask Fortunerabbit",
			"effect": "outfit_mask",
			"icons": "UiOutfitMaskDOF23Rabbit",
			"type": 1
		},
		{
			"id": 964659005,
			"name": "Outfit Mask Fox",
			"effect": "outfit_mask",
			"icons": "UiOutfitMaskAP02Fox",
			"type": 1
		},
		{
			"id": -849020465,
			"name": "Outfit Mask Ox",
			"effect": "outfit_mask",
			"icons": "UiOutfitMaskOx",
			"type": 1
		},
		{
			"id": 144876107,
			"name": "Outfit Mask Pheonix",
			"effect": "outfit_mask",
			"icons": "UiOutfitMaskAP09Phoenix",
			"type": 1
		},
		{
			"id": -1636163586,
			"name": "Outfit Mask Redface",
			"effect": "outfit_mask",
			"icons": "UiOutfitMaskRedFace",
			"type": 1
		},
		{
			"id": -938578505,
			"name": "Outfit Mask Rose",
			"effect": "outfit_mask",
			"icons": "UiOutfitMaskRose",
			"type": 1
		},
		{
			"id": 858950093,
			"name": "Outfit Mask Ski",
			"effect": "outfit_mask",
			"icons": "UiOutfitMaskDOW22YetiGoggles",
			"type": 1
		},
		{
			"id": 771982951,
			"name": "Outfit Mask Spintrick",
			"effect": "outfit_mask",
			"icons": "UiOutfitMaskAP09Quail",
			"type": 1
		},
		{
			"id": 475055967,
			"name": "Outfit Mask Tiger",
			"effect": "outfit_mask",
			"icons": "UiOutfitMaskTiger",
			"type": 1
		},
		{
			"id": 784922793,
			"name": "Outfit Mask Weasel",
			"effect": "outfit_mask",
			"icons": "UiOutfitMaskAP02Weasel",
			"type": 1
		},
		{
			"id": 43899279,
			"name": "Outfit Neck Bow",
			"effect": "outfit_neck",
			"icons": "UiOutfitNeckDOL23Bow",
			"type": 5
		},
		{
			"id": 1021908644,
			"name": "Outfit Neck Feast Ghost",
			"effect": "outfit_neck",
			"icons": "UiOutfitNeckWinterScarf",
			"type": 5
		},
		{
			"id": -1938239955,
			"name": "Outfit Neck Ocean",
			"effect": "outfit_neck",
			"icons": "UiOutfitNeckOcean",
			"type": 5
		},
		{
			"id": 1943995802,
			"name": "Outfit Neck Seaturtle",
			"effect": "outfit_neck",
			"icons": "UiOutfitNeckSeaTurtle",
			"type": 5
		},
		{
			"id": 329235560,
			"name": "Outfit Neck Summerjelly",
			"effect": "outfit_neck",
			"icons": "UiOutfitNeckDOSJellyfish",
			"type": 5
		},
		{
			"id": 70832281,
			"name": "Outfit Neck Winterscarf",
			"effect": "outfit_neck",
			"icons": "UiOutfitNeckWinterScarf",
			"type": 5
		},
		{
			"id": 8361886,
			"name": "Outfit Neck Xmas",
			"effect": "outfit_neck",
			"icons": "UiOutfitNeckXmas",
			"type": 5
		},
		{
			"id": 332997197,
			"name": "Outfit Prop Anniversaryguitar",
			"effect": "outfit_prop",
			"icons": "UiOutfitPropReskinAP14Guitar",
			"type": 4
		},
		{
			"id": 160072902,
			"name": "Outfit Prop Ap05brazier",
			"effect": "outfit_prop",
			"icons": "UiOutfitPropAP05Brazier",
			"type": 4
		},
		{
			"id": -1202427550,
			"name": "Outfit Prop Ap05piano",
			"effect": "outfit_prop",
			"icons": "UiOutfitPropAP05Piano",
			"type": 4
		},
		{
			"id": -913145276,
			"name": "Outfit Prop Ballgame",
			"effect": "outfit_prop",
			"icons": "UiOutfitPropDOW22SkyBallGoals",
			"type": 4
		},
		{
			"id": -1866832203,
			"name": "Outfit Prop Beachchaircloth",
			"effect": "outfit_prop",
			"icons": "UiOutfitPropBeachChairCloth",
			"type": 4
		},
		{
			"id": 472595010,
			"name": "Outfit Prop Beachchairwood",
			"effect": "outfit_prop",
			"icons": "UiOutfitPropBeachChairWood",
			"type": 4
		},
		{
			"id": -1158710924,
			"name": "Outfit Prop Beachrecliner",
			"effect": "outfit_prop",
			"icons": "UiOutfitPropBeachRecliner",
			"type": 4
		},
		{
			"id": 185406188,
			"name": "Outfit Prop Bloompicnic",
			"effect": "outfit_prop",
			"icons": "UiOutfitPropPicnicBlanket",
			"type": 4
		},
		{
			"id": -1096484674,
			"name": "Outfit Prop Butterflyfountain",
			"effect": "outfit_prop",
			"icons": "UiOutfitPropButterflyFountain",
			"type": 4
		},
		{
			"id": 227018419,
			"name": "Outfit Prop Fireworks",
			"effect": "outfit_prop",
			"icons": "UiOutfitPropFireworks",
			"type": 4
		},
		{
			"id": 1275481440,
			"name": "Outfit Prop Fledglingharp",
			"effect": "outfit_prop",
			"icons": "UiOutfitPropReskinHarp",
			"type": 4
		},
		{
			"id": -1333564540,
			"name": "Outfit Prop Flowerarch",
			"effect": "outfit_prop",
			"icons": "UiOutfitPropDOL23FlowerArch",
			"type": 4
		},
		{
			"id": 1621987452,
			"name": "Outfit Prop Fortuneumbrella",
			"effect": "outfit_prop",
			"icons": "UiOutfitPropDOF23Umbrella",
			"type": 4
		},
		{
			"id": -2057431024,
			"name": "Outfit Prop Fox",
			"effect": "outfit_prop",
			"icons": "UiOutfitPropAP11Fox",
			"type": 4
		},
		{
			"id": 303877523,
			"name": "Outfit Prop Gondola",
			"effect": "outfit_prop",
			"icons": "UiOutfitPropGondola",
			"type": 4
		},
		{
			"id": -1001892262,
			"name": "Outfit Prop Harp",
			"effect": "outfit_prop",
			"icons": "UiOutfitPropHarp",
			"type": 4
		},
		{
			"id": 1403584133,
			"name": "Outfit Prop Heartstaff",
			"effect": "outfit_prop",
			"icons": "UiOutfitPropDOL23HeartFireworks",
			"type": 4
		},
		{
			"id": -359346310,
			"name": "Outfit Prop Horn",
			"effect": "outfit_prop",
			"icons": "UiOutfitPropHorn",
			"type": 4
		},
		{
			"id": 1319710173,
			"name": "Outfit Prop Lantern",
			"effect": "outfit_prop",
			"icons": "UiOutfitPropLantern",
			"type": 4
		},
		{
			"id": -420852981,
			"name": "Outfit Prop Loveseesaw",
			"effect": "outfit_prop",
			"icons": "UiOutfitPropSeesaw",
			"type": 4
		},
		{
			"id": -1129614302,
			"name": "Outfit Prop Marshmallow",
			"effect": "outfit_prop",
			"icons": "UiOutfitPropDOS22MarshmallowSet",
			"type": 4
		},
		{
			"id": -834438493,
			"name": "Outfit Prop Microphone",
			"effect": "outfit_prop",
			"icons": "UiOutfitPropAP16Microphone",
			"type": 4
		},
		{
			"id": 137268536,
			"name": "Outfit Prop Microphone Aurora",
			"effect": "outfit_prop",
			"icons": "UiOutfitPropAP16Microphone",
			"type": 4
		},
		{
			"id": 1436679857,
			"name": "Outfit Prop Mischiefcat",
			"effect": "outfit_prop",
			"icons": "UiOutfitPropDOM22Cat",
			"type": 4
		},
		{
			"id": 125584301,
			"name": "Outfit Prop Mischiefpumpkin",
			"effect": "outfit_prop",
			"icons": "UiOutfitPropMischiefPumpkin",
			"type": 4
		},
		{
			"id": -797688127,
			"name": "Outfit Prop Mischieftable",
			"effect": "outfit_prop",
			"icons": "UiOutfitPropMischiefChair",
			"type": 4
		},
		{
			"id": -1419483218,
			"name": "Outfit Prop Pipebroken",
			"effect": "outfit_prop",
			"icons": "UiOutfitPropPipeBroken",
			"type": 4
		},
		{
			"id": 970364197,
			"name": "Outfit Prop Rhythmguitar",
			"effect": "outfit_prop",
			"icons": "UiOutfitPropReskinGuitar",
			"type": 4
		},
		{
			"id": -2095749161,
			"name": "Outfit Prop Seesaw",
			"effect": "outfit_prop",
			"icons": "UiOutfitPropSeesaw",
			"type": 4
		},
		{
			"id": 1440439821,
			"name": "Outfit Prop Snowglobe",
			"effect": "outfit_prop",
			"icons": "UiOutfitPropSnowGlobe",
			"type": 4
		},
		{
			"id": 1080405300,
			"name": "Outfit Prop Snowkid",
			"effect": "outfit_prop",
			"icons": "UiOutfitPropDOW22Snowman",
			"type": 4
		},
		{
			"id": 1414743743,
			"name": "Outfit Prop Summertent",
			"effect": "outfit_prop",
			"icons": "UiOutfitPropDOS22Tent",
			"type": 4
		},
		{
			"id": -1416755338,
			"name": "Outfit Prop Summerumbrella",
			"effect": "outfit_prop",
			"icons": "UiOutfitPropSummerUmbrella",
			"type": 4
		},
		{
			"id": 1064080243,
			"name": "Outfit Prop Swing",
			"effect": "outfit_prop",
			"icons": "UiOutfitPropSwing",
			"type": 4
		},
		{
			"id": 256924066,
			"name": "Outfit Prop Tablexmas",
			"effect": "outfit_prop",
			"icons": "UiOutfitPropChairXmas",
			"type": 4
		},
		{
			"id": 10058409,
			"name": "Outfit Prop Teaset",
			"effect": "outfit_prop",
			"icons": "UiOutfitPropTeaTable",
			"type": 4
		},
		{
			"id": 454864430,
			"name": "Outfit Prop Triumphhandpan",
			"effect": "outfit_prop",
			"icons": "UiOutfitPropReskinHandPan",
			"type": 4
		},
		{
			"id": -992017029,
			"name": "Outfit Prop Umbrella",
			"effect": "outfit_prop",
			"icons": "UiOutfitPropUmbrella",
			"type": 4
		},
		{
			"id": 1167393926,
			"name": "Outfit Prop Umbrella03",
			"effect": "outfit_prop",
			"icons": "UiOutfitPropAP03UmbrellaB",
			"type": 4
		},
		{
			"id": 1598845731,
			"name": "Outfit Prop Wisteriateaset",
			"effect": "outfit_prop",
			"icons": "UiOutfitPropWisteriaTea",
			"type": 4
		},
		{
			"id": 330655056,
			"name": "Outfit Wing Ap04elder",
			"effect": "outfit_wing",
			"icons": "UiOutfitCapeAP04Elder",
			"type": 3
		},
		{
			"id": -383842131,
			"name": "Outfit Wing Ap06layereda",
			"effect": "outfit_wing",
			"icons": "UiOutfitCapeAP06LayeredA",
			"type": 3
		},
		{
			"id": 1326646141,
			"name": "Outfit Wing Aurora",
			"effect": "outfit_wing",
			"icons": "UiOutfitCapeAP16ButterflyYellow",
			"type": 3
		},
		{
			"id": 625581156,
			"name": "Outfit Wing Bat",
			"effect": "outfit_wing",
			"icons": "UiOutfitCapeBat",
			"type": 3
		},
		{
			"id": 162066154,
			"name": "Outfit Wing Blossom",
			"effect": "outfit_wing",
			"icons": "UiOutfitCapeBlossom",
			"type": 3
		},
		{
			"id": 1360796960,
			"name": "Outfit Wing Butterflyyellow",
			"effect": "outfit_wing",
			"icons": "UiOutfitCapeAP16ButterflyYellow",
			"type": 3
		},
		{
			"id": 573237039,
			"name": "Outfit Wing Carp",
			"effect": "outfit_wing",
			"icons": "UiOutfitCapeFish",
			"type": 3
		},
		{
			"id": 583315364,
			"name": "Outfit Wing Catcape",
			"effect": "outfit_wing",
			"icons": "UiOutfitCapeDOM22Cat",
			"type": 3
		},
		{
			"id": -1623262339,
			"name": "Outfit Wing Director",
			"effect": "outfit_wing",
			"icons": "UiOutfitCapeAP05Director",
			"type": 3
		},
		{
			"id": 2079599063,
			"name": "Outfit Wing Earthday",
			"effect": "outfit_wing",
			"icons": "UiOutfitCapeSprout",
			"type": 3
		},
		{
			"id": -445538750,
			"name": "Outfit Wing Fortune",
			"effect": "outfit_wing",
			"icons": "UiOutfitCapeFortune",
			"type": 3
		},
		{
			"id": -940505450,
			"name": "Outfit Wing Fur",
			"effect": "outfit_wing",
			"icons": "UiOutfitCapeDOW22YetiFur",
			"type": 3
		},
		{
			"id": 1402240423,
			"name": "Outfit Wing Greencoat",
			"effect": "outfit_wing",
			"icons": "UiOutfitCapeAP11GreenCoat",
			"type": 3
		},
		{
			"id": 1375571404,
			"name": "Outfit Wing Lightseeker",
			"effect": "outfit_wing",
			"icons": "UiOutfitCapeAP03Biolum",
			"type": 3
		},
		{
			"id": 329684861,
			"name": "Outfit Wing Ocean",
			"effect": "outfit_wing",
			"icons": "UiOutfitCapeOcean",
			"type": 3
		},
		{
			"id": 939730131,
			"name": "Outfit Wing Orangelove",
			"effect": "outfit_wing",
			"icons": "UiOutfitCapeAP16OrangeLove",
			"type": 3
		},
		{
			"id": -6043825,
			"name": "Outfit Wing Petal",
			"effect": "outfit_wing",
			"icons": "UiOutfitCapeAP03Petal",
			"type": 3
		},
		{
			"id": -1822337532,
			"name": "Outfit Wing Pheonix",
			"effect": "outfit_wing",
			"icons": "UiOutfitCapeAP09Phoenix",
			"type": 3
		},
		{
			"id": -308941587,
			"name": "Outfit Wing Postman",
			"effect": "outfit_wing",
			"icons": "UiOutfitCapeAP09Waves",
			"type": 3
		},
		{
			"id": -195929339,
			"name": "Outfit Wing Rainbow",
			"effect": "outfit_wing",
			"icons": "UiOutfitCapeRainbow",
			"type": 3
		},
		{
			"id": -2087661926,
			"name": "Outfit Wing Scarf",
			"effect": "outfit_wing",
			"icons": "UiOutfitCapeAP11Scarf",
			"type": 3
		},
		{
			"id": -700035318,
			"name": "Outfit Wing Seaturtle",
			"effect": "outfit_wing",
			"icons": "UiOutfitCapeSeaTurtle",
			"type": 3
		},
		{
			"id": -784831205,
			"name": "Outfit Wing Snowflake",
			"effect": "outfit_wing",
			"icons": "UiOutfitCapeSnowflake",
			"type": 3
		},
		{
			"id": 1031127004,
			"name": "Outfit Wing Spintrick",
			"effect": "outfit_wing",
			"icons": "UiOutfitCapeAP09Waves",
			"type": 3
		},
		{
			"id": 747642100,
			"name": "Outfit Wing Sprout",
			"effect": "outfit_wing",
			"icons": "UiOutfitCapeSprout",
			"type": 3
		},
		{
			"id": 540856305,
			"name": "Outfit Wing Tgc",
			"effect": "outfit_wing",
			"icons": "UiOutfitCapeTGC",
			"type": 3
		},
		{
			"id": 549258087,
			"name": "Outfit Wing Tulip",
			"effect": "outfit_wing",
			"icons": "UiOutfitCapeTulip",
			"type": 3
		},
		{
			"id": 930203946,
			"name": "Outfit Wing Webcape",
			"effect": "outfit_wing",
			"icons": "UiOutfitCapeSpiderWeb",
			"type": 3
		},
		{
			"id": 1762827508,
			"name": "Outfit Wing Winterelder",
			"effect": "outfit_wing",
			"icons": "UiOutfitCapeWinterElder",
			"type": 3
		},
		{
			"id": -1244390069,
			"name": "Outfit Wing Wisteria",
			"effect": "outfit_wing",
			"icons": "UiOutfitCapeWisteria",
			"type": 3
		},
		{
			"id": 769892976,
			"name": "Outfit Wing Witheredcape",
			"effect": "outfit_wing",
			"icons": "UiOutfitCapeWithered",
			"type": 3
		},
		{
			"id": 1306675982,
			"name": "Outfit Wing Xmas",
			"effect": "outfit_wing",
			"icons": "UiOutfitCapeSanta",
			"type": 3
		},
		{
			"id": -1463943689,
			"name": "Rain Drain 0 5x",
			"effect": "rain_drain_mult",
			"icons": "UiEmoteStress",
			"type": 5
		},
		{
			"id": 1677246236,
			"name": "Relationship Allow Bearhug",
			"effect": "relationship_allow",
			"icons": "UiEmoteSocialBearHug",
			"type": 5
		},
		{
			"id": 1405645877,
			"name": "Relationship Allow Carry",
			"effect": "relationship_allow",
			"icons": "UiSocialCarryB",
			"type": 5
		},
		{
			"id": 2137753158,
			"name": "Relationship Allow Playfight",
			"effect": "relationship_allow",
			"icons": "UiSocialPlayfight",
			"type": 5
		},
		{
			"id": 998754260,
			"name": "Relationship Allow Warp",
			"effect": "relationship_allow",
			"icons": "UiSocialTeleport",
			"type": 5
		},
		{
			"id": 953841005,
			"name": "Relationship Flair Soulmate",
			"effect": "relationship_flair",
			"icons": "UiMiscYouAndI",
			"type": 5
		},
		{
			"id": -932650381,
			"name": "Repellant Krill",
			"effect": "repellant_krill",
			"icons": "UIMenuBuffKrillRepellent",
			"type": 5
		},
		{
			"id": 1725047129,
			"name": "Shout Crab",
			"effect": "shout",
			"icons": "UiEmoteCallCrab",
			"type": 5
		},
		{
			"id": -957441587,
			"name": "Shout Jelly",
			"effect": "shout",
			"icons": "UiEmoteCallJellyfish",
			"type": 5
		},
		{
			"id": -1881863468,
			"name": "Shout Kizunaaicn",
			"effect": "shout",
			"icons": "UiOutfitHairKizunaAiRed",
			"type": 2
		},
		{
			"id": 1814753890,
			"name": "Shout Manta",
			"effect": "shout",
			"icons": "UiEmoteCallManta",
			"type": 5
		},
		{
			"id": -1879316162,
			"name": "Size Large 3x",
			"effect": "size_mult",
			"icons": "UiMenuBuffHuge",
			"type": 5
		},
		{
			"id": 2142718166,
			"name": "Size Small 3x",
			"effect": "size_mult",
			"icons": "UiMenuBuffTiny",
			"type": 5
		},
		{
			"id": -356890497,
			"name": "Size Small X",
			"effect": "outfit_hair",
			"icons": "UiWip",
			"type": 5
		},
		{
			"id": -392849190,
			"name": "Teleport Aurora Concert",
			"effect": "teleport",
			"icons": "UiOutfitCapeAP16ButterflyYellow",
			"type": 3
		},
		{
			"id": 428008620,
			"name": "Teleport Birthdaycrab",
			"effect": "teleport",
			"icons": "UiOutfitHornBirthdayHat01",
			"type": 5
		},
		{
			"id": -1766441122,
			"name": "Teleport Figurineskykid Se",
			"effect": "teleport",
			"icons": "UiMenuSocialMask",
			"type": 5
		},
		{
			"id": 224110574,
			"name": "Teleport Forest Cave",
			"effect": "teleport",
			"icons": "ConstellationImageRain",
			"type": 5
		},
		{
			"id": -1256468339,
			"name": "Teleport Forest Elder",
			"effect": "teleport",
			"icons": "ConstellationImageRain",
			"type": 5
		},
		{
			"id": -210323960,
			"name": "Teleport Forgotten Ark",
			"effect": "teleport",
			"icons": "ConstellationImageDusk",
			"type": 5
		},
		{
			"id": 1660914074,
			"name": "Teleport Hermit Valley",
			"effect": "teleport",
			"icons": "ConstellationImageSunset",
			"type": 5
		},
		{
			"id": 103122035,
			"name": "Teleport Isle Elder",
			"effect": "teleport",
			"icons": "ConstellationImageDawn",
			"type": 5
		},
		{
			"id": 282325575,
			"name": "Teleport Nature Turtle",
			"effect": "teleport",
			"icons": "UiMenuBuffSeaTurtle",
			"type": 5
		},
		{
			"id": -529345906,
			"name": "Teleport Oreo",
			"effect": "teleport",
			"icons": "UiEmoteCallDefault",
			"type": 5
		},
		{
			"id": -1633629698,
			"name": "Teleport Prairie Elder",
			"effect": "teleport",
			"icons": "ConstellationImageDay",
			"type": 5
		},
		{
			"id": 598305233,
			"name": "Teleport Sanctuary Island",
			"effect": "teleport",
			"icons": "ConstellationImageDay",
			"type": 5
		},
		{
			"id": 248080515,
			"name": "Teleport Valley Elder",
			"effect": "teleport",
			"icons": "ConstellationImageSunset",
			"type": 5
		},
		{
			"id": -1172691679,
			"name": "Teleport Wasteland Elder",
			"effect": "teleport",
			"icons": "ConstellationImageDusk",
			"type": 5
		},
		{
			"id": 1153544860,
			"name": "Teleport You And I",
			"effect": "teleport",
			"icons": "UiMiscYouAndI",
			"type": 5
		},
		{
			"id": 809787442,
			"name": "Timeline Aurora Concert",
			"effect": "timeline",
			"icons": "UiOutfitCapeAP16ButterflyYellow",
			"type": 3
		},
		{
			"id": 539651423,
			"name": "Timeline Daynight",
			"effect": "timeline",
			"icons": "UiMenuConstellationHome",
			"type": 5
		},
		{
			"id": -284883787,
			"name": "Timeline Fortune Fireworks",
			"effect": "timeline",
			"icons": "UiOutfitPropFireworks",
			"type": 4
		},
		{
			"id": 898079755,
			"name": "Timeline Newyear Fireworks",
			"effect": "timeline",
			"icons": "UiOutfitPropFireworks",
			"type": 4
		},
		{
			"id": -224828914,
			"name": "Trail Amaranthpink",
			"effect": "trail",
			"icons": "UiMenuBuffTrail",
			"type": 5
		},
		{
			"id": 1318288330,
			"name": "Trail Aquamarine",
			"effect": "trail",
			"icons": "UiMenuBuffTrail",
			"type": 5
		},
		{
			"id": -176902809,
			"name": "Trail Black",
			"effect": "trail",
			"icons": "UiMenuBuffTrail",
			"type": 5
		},
		{
			"id": -1951801352,
			"name": "Trail Blue",
			"effect": "trail",
			"icons": "UiMenuBuffTrail",
			"type": 5
		},
		{
			"id": 1918290563,
			"name": "Trail Cyan",
			"effect": "trail",
			"icons": "UiMenuBuffTrail",
			"type": 5
		},
		{
			"id": 637646527,
			"name": "Trail Green",
			"effect": "trail",
			"icons": "UiMenuBuffTrail",
			"type": 5
		},
		{
			"id": -1527316661,
			"name": "Trail Magenta",
			"effect": "trail",
			"icons": "UiMenuBuffTrail",
			"type": 5
		},
		{
			"id": -349598416,
			"name": "Trail Mayablue",
			"effect": "trail",
			"icons": "UiMenuBuffTrail",
			"type": 5
		},
		{
			"id": 1237283438,
			"name": "Trail Orange",
			"effect": "trail",
			"icons": "UiMenuBuffTrail",
			"type": 5
		},
		{
			"id": 470393304,
			"name": "Trail Pink",
			"effect": "trail",
			"icons": "UiMenuBuffTrail",
			"type": 5
		},
		{
			"id": 1891264165,
			"name": "Trail Psblue",
			"effect": "trail",
			"icons": "UiMenuBuffTrail",
			"type": 5
		},
		{
			"id": -1071076330,
			"name": "Trail Purple",
			"effect": "trail",
			"icons": "UiMenuBuffTrail",
			"type": 5
		},
		{
			"id": 147016038,
			"name": "Trail Rainbow",
			"effect": "trail_rainbow",
			"icons": "UiMenuBuffTrail",
			"type": 5
		},
		{
			"id": -1304862813,
			"name": "Trail Red",
			"effect": "trail",
			"icons": "UiMenuBuffTrail",
			"type": 5
		},
		{
			"id": -1354381164,
			"name": "Trail Yellow",
			"effect": "trail",
			"icons": "UiMenuBuffTrail",
			"type": 5
		},
		{
			"id": -1727483534,
			"name": "Wax 2x",
			"effect": "wax_collection_mult",
			"icons": "UiMenuBuffDoubleWax",
			"type": 5
		},
		{
			"id": -1362469224,
			"name": "Wing Gain",
			"effect": "wing_add",
			"icons": "UiOutfitCape",
			"type": 3
		}
	]
)"));