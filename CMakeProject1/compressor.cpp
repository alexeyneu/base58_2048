

#include "CMakeProject1.h"
#include <openssl/sha.h>
#include <openssl/bn.h>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cstring>
#include <sstream>
#include <iomanip>


const	std::string bin2hex(const unsigned char* p, size_t length) {
	std::stringstream f;
	f << std::hex << std::setfill('0');
	for (int i = 0; i < length; i++) f << std::setw(2) << (int)p[i];
	return f.str();
}

size_t hex2bin(unsigned char* p, const char* hexstr, const size_t length) {
	size_t wcount = 0;
	while (wcount++ < length && *hexstr && *(hexstr + 1)) {    //last condition cause np if check fails on middle one.thats coz of short-circuit evaluation
		sscanf(hexstr, "%2hhx", p++);  //7x slower than tables but doesnt metter 
		hexstr = hexstr + 2;
	}
	return  --wcount;     // error check here is a waste  
}



struct offstring
{
	static const std::vector<std::string> disclaimer;
};

int main(int argc, char *argv[])
{
	
	if (argc > 3)
	{
		std::cerr << std::endl << "no go" << std::endl;
		return 0;
	}
	if (argc == 1)
	{
		std::cerr << std::endl << "where's the" << std::endl;
		return 0;
	}
	if (argc == 3 && ((std::string(argv[1]) == "-wif24" == false) && (std::string(argv[1]) == "-hex32_24" == false)))
	{
		std::cerr << std::endl << "no go" << std::endl;
		return 0;
	}
	
	std::vector<std::string> b;

	std::ifstream fw(argc == 3 ? argv[2] : argv[1]);
	if (fw.fail())
	{
		std::cerr << std::endl << "not found" << std::endl;
		return 0;
	}

	do 
	{
		std::string last;
		fw >> last;
		if (fw.fail()) break;
		b.insert(b.cend(), last);
	} while (fw.bad() == false);



	unsigned char fx = 58;
	BIGNUM* balance_eth_f = BN_lebin2bn(&fx, 1, NULL);
	unsigned short wa = 2048;
	BIGNUM* balance_eth_lake = BN_lebin2bn((unsigned char *)&wa, 2, NULL);

    BN_CTX *bz = BN_CTX_new();

	bool w = false;

	BIGNUM* balance_eth_ex_e = BN_new();
	BIGNUM* balance_eth_exm_e = BN_new();
	BIGNUM* balance_eth_remmi_e = BN_new();
	BIGNUM* balance_eth_h_e = BN_new();

	BN_zero(balance_eth_ex_e);
	BN_one(balance_eth_h_e);
	int zerocount = 0;

	while (std::find(offstring::disclaimer.cbegin(), offstring::disclaimer.cend(), *b.cbegin()) == offstring::disclaimer.cbegin())
	{
		zerocount++;
		b.erase(b.cbegin());
	}

	for (int kwe = b.size() - 1; kwe + 1> 0; kwe--)
	{
		auto rexx = std::find(offstring::disclaimer.cbegin(), offstring::disclaimer.cend(), b[kwe]);

		if (rexx == offstring::disclaimer.cend())
		{
			BN_free(balance_eth_ex_e);
			BN_free(balance_eth_exm_e);
			BN_free(balance_eth_remmi_e);
			BN_free(balance_eth_h_e);
			BN_free(balance_eth_f);
			BN_free(balance_eth_lake);
			BN_CTX_free(bz);


			return -4;

		}

		unsigned int exp = std::distance(offstring::disclaimer.cbegin(), rexx) ;
		BIGNUM* balance_eth_exmk_e = BN_lebin2bn((unsigned char*)&exp, 4, NULL);
		BN_mul(balance_eth_exm_e, balance_eth_h_e, balance_eth_exmk_e, bz);
		BN_add(balance_eth_ex_e, balance_eth_ex_e, balance_eth_exm_e);
		BN_mul(balance_eth_h_e, balance_eth_h_e, balance_eth_lake, bz);
		BN_free(balance_eth_exmk_e);
	}
	int cw = 0;
	unsigned short tr_e = 0;

	static const char b58digits_ordered[59] = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz";
	std::string harbour;

	while (w == false)
	{
		BN_div(balance_eth_ex_e, balance_eth_remmi_e, balance_eth_ex_e, balance_eth_f, bz);
		BN_bn2lebinpad(balance_eth_remmi_e, (unsigned char*)&tr_e, 2);
		harbour = harbour + b58digits_ordered[tr_e];

		w = BN_is_zero(balance_eth_ex_e);
	}
	std::reverse((unsigned char*)&harbour[0], (unsigned char*)&harbour[0] + harbour.size());

	for (int h = 0; h < zerocount; h++)
		harbour.insert(harbour.cbegin(), '1');

	if (argc == 2)
	{
		std::cout << std::endl << harbour << std::endl;
		BN_free(balance_eth_ex_e);
		BN_free(balance_eth_exm_e);
		BN_free(balance_eth_remmi_e);
		BN_free(balance_eth_h_e);
		BN_free(balance_eth_f);
		BN_free(balance_eth_lake);
		BN_CTX_free(bz);
	}
	if ((argc == 2 == false) && std::string(argv[1]) == "-wif24")
	{
		if (b.size() == 24 == false)
		{
			std::cerr << std::endl << "do not mess with it" << std::endl;
			BN_free(balance_eth_ex_e);
			BN_free(balance_eth_exm_e);
			BN_free(balance_eth_remmi_e);
			BN_free(balance_eth_h_e);
			BN_free(balance_eth_f);
			BN_free(balance_eth_lake);
			BN_CTX_free(bz);
			return -5;
		}
		unsigned char bc[750] = {};
		size_t wq = 750;
		bool ho = b58tobin((void*)bc, &wq, harbour.c_str(), harbour.length());
		ho = b58tobin((void*)bc, &wq, harbour.c_str(), harbour.length());

		unsigned char wb_final_compressed[250] = {};
		unsigned char wb_f_compressed[250] = {};

		wb_final_compressed[0] = 0x80;

		memcpy(wb_final_compressed + 1, bc, wq);
		wb_final_compressed[wq + 1] = 0x01;

		unsigned char h_compressed[250] = {};
		unsigned char hf_compressed[250] = {};
		memcpy(wb_f_compressed, wb_final_compressed, wq + 2);
		SHA256(wb_f_compressed, wq + 2, h_compressed);
		SHA256(h_compressed, 32, hf_compressed);
		memcpy(wb_final_compressed + wq + 2, hf_compressed, 4);
		char* t_compressed = new char[750]();
		size_t cw_copmressed = 750;
		b58enc(t_compressed, &cw_copmressed, (void*)wb_final_compressed, (size_t)(38));


		unsigned char wb_final[250] = {};
		unsigned char wb_f[250] = {};
		wb_final[0] = 0x80;

		memcpy(wb_final + 1, bc, wq);
		unsigned char h[250] = {};
		unsigned char hf[250] = {};
		memcpy(wb_f, wb_final, wq + 1);
		SHA256(wb_f, wq + 1, h);
		SHA256(h, 32, hf);
		memcpy(wb_final + wq + 1, hf, 4);
		char* t = new char[750]();
		size_t cw = 750;
		b58enc(t, &cw, (void*)wb_final, (size_t)(1 + 32 + 4));

		std::string whydah = t;
		std::cout << std::endl << whydah << std::endl;
		std::string mill = t_compressed;
		std::cout << std::endl << mill << std::endl;

		BN_free(balance_eth_ex_e);
		BN_free(balance_eth_exm_e);
		BN_free(balance_eth_remmi_e);
		BN_free(balance_eth_h_e);
		BN_free(balance_eth_f);
		BN_free(balance_eth_lake);
		BN_CTX_free(bz);
		delete[] t_compressed;
		delete[] t;
	}
	if ((argc == 2 == false) && std::string(argv[1]) == "-hex32_24")
	{
		if (b.size() == 24 == false)
		{
			std::cerr << std::endl << "do not mess with it" << std::endl;
			BN_free(balance_eth_ex_e);
			BN_free(balance_eth_exm_e);
			BN_free(balance_eth_remmi_e);
			BN_free(balance_eth_h_e);
			BN_free(balance_eth_f);
			BN_free(balance_eth_lake);
			BN_CTX_free(bz);
			return -5;
		}
		unsigned char bc[850] = {};
		size_t wq = 850;
		bool ho = b58tobin((void*)bc, &wq, harbour.c_str(), harbour.length());
		ho = b58tobin((void*)bc, &wq, harbour.c_str(), harbour.length());

		unsigned char wb_final[250] = {};

		memcpy(wb_final, bc, wq);
		;

		std::string draw = bin2hex(wb_final, 32);
		std::cout << std::endl << draw << std::endl;

		BN_free(balance_eth_ex_e);
		BN_free(balance_eth_exm_e);
		BN_free(balance_eth_remmi_e);
		BN_free(balance_eth_h_e);
		BN_free(balance_eth_f);
		BN_free(balance_eth_lake);
		BN_CTX_free(bz);
	}
	return 0;
}


const std::vector<std::string> offstring::disclaimer = { "abandon" , "ability" , "able" , "about" , "above" , "absent" , "absorb" , "abstract" , "absurd" , "abuse" , "access" , "accident" , "account" , "accuse" , "achieve" , "acid" , "acoustic" , "acquire" ,
"across" , "act" , "action" , "actor" , "actress" , "actual" , "adapt" , "add" , "addict" , "address" , "adjust" , "admit" , "adult" , "advance" , "advice" , "aerobic" , "affair" , "afford" , "afraid" , "again" , "age" , "agent" , "agree" , "ahead" ,
"aim" , "air" , "airport" , "aisle" , "alarm" , "album" , "alcohol" , "alert" , "alien" , "all" , "alley" , "allow" , "almost" , "alone" , "alpha" , "already" , "also" , "alter" , "always" , "amateur" , "amazing" , "among" , "amount" , "amused" ,
"analyst" , "anchor" , "ancient" , "anger" , "angle" , "angry" , "animal" , "ankle" , "announce" , "annual" , "another" , "answer" , "antenna" , "antique" , "anxiety" , "any" , "apart" , "apology" , "appear" , "apple" , "approve" , "april" , "arch" ,
"arctic" , "area" , "arena" , "argue" , "arm" , "armed" , "armor" , "army" , "around" , "arrange" , "arrest" , "arrive" , "arrow" , "art" , "artefact" , "artist" , "artwork" , "ask" , "aspect" , "assault" , "asset" , "assist" , "assume" , "asthma" ,
"athlete" , "atom" , "attack" , "attend" , "attitude" , "attract" , "auction" , "audit" , "august" , "aunt" , "author" , "auto" , "autumn" , "average" , "avocado" , "avoid" , "awake" , "aware" , "away" , "awesome" , "awful" , "awkward" , "axis" ,
"baby" , "bachelor" , "bacon" , "badge" , "bag" , "balance" , "balcony" , "ball" , "bamboo" , "banana" , "banner" , "bar" , "barely" , "bargain" , "barrel" , "base" , "basic" , "basket" , "battle" , "beach" , "bean" , "beauty" , "because" , "become" ,
"beef" , "before" , "begin" , "behave" , "behind" , "believe" , "below" , "belt" , "bench" , "benefit" , "best" , "betray" , "better" , "between" , "beyond" , "bicycle" , "bid" , "bike" , "bind" , "biology" , "bird" , "birth" , "bitter" , "black" ,
"blade" , "blame" , "blanket" , "blast" , "bleak" , "bless" , "blind" , "blood" , "blossom" , "blouse" , "blue" , "blur" , "blush" , "board" , "boat" , "body" , "boil" , "bomb" , "bone" , "bonus" , "book" , "boost" , "border" , "boring" , "borrow" ,
"boss" , "bottom" , "bounce" , "box" , "boy" , "bracket" , "brain" , "brand" , "brass" , "brave" , "bread" , "breeze" , "brick" , "bridge" , "brief" , "bright" , "bring" , "brisk" , "broccoli" , "broken" , "bronze" , "broom" , "brother" , "brown" ,
"brush" , "bubble" , "buddy" , "budget" , "buffalo" , "build" , "bulb" , "bulk" , "bullet" , "bundle" , "bunker" , "burden" , "burger" , "burst" , "bus" , "business" , "busy" , "butter" , "buyer" , "buzz" , "cabbage" , "cabin" , "cable" , "cactus" ,
"cage" , "cake" , "call" , "calm" , "camera" , "camp" , "can" , "canal" , "cancel" , "candy" , "cannon" , "canoe" , "canvas" , "canyon" , "capable" , "capital" , "captain" , "car" , "carbon" , "card" , "cargo" , "carpet" , "carry" , "cart" , "case" ,
"cash" , "casino" , "castle" , "casual" , "cat" , "catalog" , "catch" , "category" , "cattle" , "caught" , "cause" , "caution" , "cave" , "ceiling" , "celery" , "cement" , "census" , "century" , "cereal" , "certain" , "chair" , "chalk" , "champion" ,
"change" , "chaos" , "chapter" , "charge" , "chase" , "chat" , "cheap" , "check" , "cheese" , "chef" , "cherry" , "chest" , "chicken" , "chief" , "child" , "chimney" , "choice" , "choose" , "chronic" , "chuckle" , "chunk" , "churn" , "cigar" ,
"cinnamon" , "circle" , "citizen" , "city" , "civil" , "claim" , "clap" , "clarify" , "claw" , "clay" , "clean" , "clerk" , "clever" , "click" , "client" , "cliff" , "climb" , "clinic" , "clip" , "clock" , "clog" , "close" , "cloth" , "cloud" ,
"clown" , "club" , "clump" , "cluster" , "clutch" , "coach" , "coast" , "coconut" , "code" , "coffee" , "coil" , "coin" , "collect" , "color" , "column" , "combine" , "come" , "comfort" , "comic" , "common" , "company" , "concert" , "conduct" ,
"confirm" , "congress" , "connect" , "consider" , "control" , "convince" , "cook" , "cool" , "copper" , "copy" , "coral" , "core" , "corn" , "correct" , "cost" , "cotton" , "couch" , "country" , "couple" , "course" , "cousin" , "cover" , "coyote" ,
"crack" , "cradle" , "craft" , "cram" , "crane" , "crash" , "crater" , "crawl" , "crazy" , "cream" , "credit" , "creek" , "crew" , "cricket" , "crime" , "crisp" , "critic" , "crop" , "cross" , "crouch" , "crowd" , "crucial" , "cruel" , "cruise" ,
"crumble" , "crunch" , "crush" , "cry" , "crystal" , "cube" , "culture" , "cup" , "cupboard" , "curious" , "current" , "curtain" , "curve" , "cushion" , "custom" , "cute" , "cycle" , "dad" , "damage" , "damp" , "dance" , "danger" , "daring" , "dash" ,
"daughter" , "dawn" , "day" , "deal" , "debate" , "debris" , "decade" , "december" , "decide" , "decline" , "decorate" , "decrease" , "deer" , "defense" , "define" , "defy" , "degree" , "delay" , "deliver" , "demand" , "demise" , "denial" , "dentist" ,
"deny" , "depart" , "depend" , "deposit" , "depth" , "deputy" , "derive" , "describe" , "desert" , "design" , "desk" , "despair" , "destroy" , "detail" , "detect" , "develop" , "device" , "devote" , "diagram" , "dial" , "diamond" , "diary" , "dice" ,
"diesel" , "diet" , "differ" , "digital" , "dignity" , "dilemma" , "dinner" , "dinosaur" , "direct" , "dirt" , "disagree" , "discover" , "disease" , "dish" , "dismiss" , "disorder" , "display" , "distance" , "divert" , "divide" , "divorce" , "dizzy" ,
"doctor" , "document" , "dog" , "doll" , "dolphin" , "domain" , "donate" , "donkey" , "donor" , "door" , "dose" , "double" , "dove" , "draft" , "dragon" , "drama" , "drastic" , "draw" , "dream" , "dress" , "drift" , "drill" , "drink" , "drip" , "drive" ,
"drop" , "drum" , "dry" , "duck" , "dumb" , "dune" , "during" , "dust" , "dutch" , "duty" , "dwarf" , "dynamic" , "eager" , "eagle" , "early" , "earn" , "earth" , "easily" , "east" , "easy" , "echo" , "ecology" , "economy" , "edge" , "edit" , "educate" ,
"effort" , "egg" , "eight" , "either" , "elbow" , "elder" , "electric" , "elegant" , "element" , "elephant" , "elevator" , "elite" , "else" , "embark" , "embody" , "embrace" , "emerge" , "emotion" , "employ" , "empower" , "empty" , "enable" , "enact" ,
"end" , "endless" , "endorse" , "enemy" , "energy" , "enforce" , "engage" , "engine" , "enhance" , "enjoy" , "enlist" , "enough" , "enrich" , "enroll" , "ensure" , "enter" , "entire" , "entry" , "envelope" , "episode" , "equal" , "equip" , "era" ,
"erase" , "erode" , "erosion" , "error" , "erupt" , "escape" , "essay" , "essence" , "estate" , "eternal" , "ethics" , "evidence" , "evil" , "evoke" , "evolve" , "exact" , "example" , "excess" , "exchange" , "excite" , "exclude" , "excuse" , "execute" ,
"exercise" , "exhaust" , "exhibit" , "exile" , "exist" , "exit" , "exotic" , "expand" , "expect" , "expire" , "explain" , "expose" , "express" , "extend" , "extra" , "eye" , "eyebrow" , "fabric" , "face" , "faculty" , "fade" , "faint" , "faith" ,
"fall" , "false" , "fame" , "family" , "famous" , "fan" , "fancy" , "fantasy" , "farm" , "fashion" , "fat" , "fatal" , "father" , "fatigue" , "fault" , "favorite" , "feature" , "february" , "federal" , "fee" , "feed" , "feel" , "female" , "fence" ,
"festival" , "fetch" , "fever" , "few" , "fiber" , "fiction" , "field" , "figure" , "file" , "film" , "filter" , "final" , "find" , "fine" , "finger" , "finish" , "fire" , "firm" , "first" , "fiscal" , "fish" , "fit" , "fitness" , "fix" , "flag" ,
"flame" , "flash" , "flat" , "flavor" , "flee" , "flight" , "flip" , "float" , "flock" , "floor" , "flower" , "fluid" , "flush" , "fly" , "foam" , "focus" , "fog" , "foil" , "fold" , "follow" , "food" , "foot" , "force" , "forest" , "forget" ,
"fork" , "fortune" , "forum" , "forward" , "fossil" , "foster" , "found" , "fox" , "fragile" , "frame" , "frequent" , "fresh" , "friend" , "fringe" , "frog" , "front" , "frost" , "frown" , "frozen" , "fruit" , "fuel" , "fun" , "funny" , "furnace" ,
"fury" , "future" , "gadget" , "gain" , "galaxy" , "gallery" , "game" , "gap" , "garage" , "garbage" , "garden" , "garlic" , "garment" , "gas" , "gasp" , "gate" , "gather" , "gauge" , "gaze" , "general" , "genius" , "genre" , "gentle" , "genuine" ,
"gesture" , "ghost" , "giant" , "gift" , "giggle" , "ginger" , "giraffe" , "girl" , "give" , "glad" , "glance" , "glare" , "glass" , "glide" , "glimpse" , "globe" , "gloom" , "glory" , "glove" , "glow" , "glue" , "goat" , "goddess" , "gold" , "good" ,
"goose" , "gorilla" , "gospel" , "gossip" , "govern" , "gown" , "grab" , "grace" , "grain" , "grant" , "grape" , "grass" , "gravity" , "great" , "green" , "grid" , "grief" , "grit" , "grocery" , "group" , "grow" , "grunt" , "guard" , "guess" , "guide" ,
"guilt" , "guitar" , "gun" , "gym" , "habit" , "hair" , "half" , "hammer" , "hamster" , "hand" , "happy" , "harbor" , "hard" , "harsh" , "harvest" , "hat" , "have" , "hawk" , "hazard" , "head" , "health" , "heart" , "heavy" , "hedgehog" , "height" ,
"hello" , "helmet" , "help" , "hen" , "hero" , "hidden" , "high" , "hill" , "hint" , "hip" , "hire" , "history" , "hobby" , "hockey" , "hold" , "hole" , "holiday" , "hollow" , "home" , "honey" , "hood" , "hope" , "horn" , "horror" , "horse" , "hospital" ,
"host" , "hotel" , "hour" , "hover" , "hub" , "huge" , "human" , "humble" , "humor" , "hundred" , "hungry" , "hunt" , "hurdle" , "hurry" , "hurt" , "husband" , "hybrid" , "ice" , "icon" , "idea" , "identify" , "idle" , "ignore" , "ill" , "illegal" ,
"illness" , "image" , "imitate" , "immense" , "immune" , "impact" , "impose" , "improve" , "impulse" , "inch" , "include" , "income" , "increase" , "index" , "indicate" , "indoor" , "industry" , "infant" , "inflict" , "inform" , "inhale" , "inherit" ,
"initial" , "inject" , "injury" , "inmate" , "inner" , "innocent" , "input" , "inquiry" , "insane" , "insect" , "inside" , "inspire" , "install" , "intact" , "interest" , "into" , "invest" , "invite" , "involve" , "iron" , "island" , "isolate" ,
"issue" , "item" , "ivory" , "jacket" , "jaguar" , "jar" , "jazz" , "jealous" , "jeans" , "jelly" , "jewel" , "job" , "join" , "joke" , "journey" , "joy" , "judge" , "juice" , "jump" , "jungle" , "junior" , "junk" , "just" , "kangaroo" , "keen" ,
"keep" , "ketchup" , "key" , "kick" , "kid" , "kidney" , "kind" , "kingdom" , "kiss" , "kit" , "kitchen" , "kite" , "kitten" , "kiwi" , "knee" , "knife" , "knock" , "know" , "lab" , "label" , "labor" , "ladder" , "lady" , "lake" , "lamp" , "language" ,
"laptop" , "large" , "later" , "latin" , "laugh" , "laundry" , "lava" , "law" , "lawn" , "lawsuit" , "layer" , "lazy" , "leader" , "leaf" , "learn" , "leave" , "lecture" , "left" , "leg" , "legal" , "legend" , "leisure" , "lemon" , "lend" , "length" ,
"lens" , "leopard" , "lesson" , "letter" , "level" , "liar" , "liberty" , "library" , "license" , "life" , "lift" , "light" , "like" , "limb" , "limit" , "link" , "lion" , "liquid" , "list" , "little" , "live" , "lizard" , "load" , "loan" , "lobster" ,
"local" , "lock" , "logic" , "lonely" , "long" , "loop" , "lottery" , "loud" , "lounge" , "love" , "loyal" , "lucky" , "luggage" , "lumber" , "lunar" , "lunch" , "luxury" , "lyrics" , "machine" , "mad" , "magic" , "magnet" , "maid" , "mail" , "main" ,
"major" , "make" , "mammal" , "man" , "manage" , "mandate" , "mango" , "mansion" , "manual" , "maple" , "marble" , "march" , "margin" , "marine" , "market" , "marriage" , "mask" , "mass" , "master" , "match" , "material" , "math" , "matrix" , "matter" ,
"maximum" , "maze" , "meadow" , "mean" , "measure" , "meat" , "mechanic" , "medal" , "media" , "melody" , "melt" , "member" , "memory" , "mention" , "menu" , "mercy" , "merge" , "merit" , "merry" , "mesh" , "message" , "metal" , "method" , "middle" ,
"midnight" , "milk" , "million" , "mimic" , "mind" , "minimum" , "minor" , "minute" , "miracle" , "mirror" , "misery" , "miss" , "mistake" , "mix" , "mixed" , "mixture" , "mobile" , "model" , "modify" , "mom" , "moment" , "monitor" , "monkey" ,
"monster" , "month" , "moon" , "moral" , "more" , "morning" , "mosquito" , "mother" , "motion" , "motor" , "mountain" , "mouse" , "move" , "movie" , "much" , "muffin" , "mule" , "multiply" , "muscle" , "museum" , "mushroom" , "music" , "must" ,
"mutual" , "myself" , "mystery" , "myth" , "naive" , "name" , "napkin" , "narrow" , "nasty" , "nation" , "nature" , "near" , "neck" , "need" , "negative" , "neglect" , "neither" , "nephew" , "nerve" , "nest" , "net" , "network" , "neutral" ,
"never" , "news" , "next" , "nice" , "night" , "noble" , "noise" , "nominee" , "noodle" , "normal" , "north" , "nose" , "notable" , "note" , "nothing" , "notice" , "novel" , "now" , "nuclear" , "number" , "nurse" , "nut" , "oak" , "obey" ,
"object" , "oblige" , "obscure" , "observe" , "obtain" , "obvious" , "occur" , "ocean" , "october" , "odor" , "off" , "offer" , "office" , "often" , "oil" , "okay" , "old" , "olive" , "olympic" , "omit" , "once" , "one" , "onion" , "online" ,
"only" , "open" , "opera" , "opinion" , "oppose" , "option" , "orange" , "orbit" , "orchard" , "order" , "ordinary" , "organ" , "orient" , "original" , "orphan" , "ostrich" , "other" , "outdoor" , "outer" , "output" , "outside" , "oval" , "oven" ,
"over" , "own" , "owner" , "oxygen" , "oyster" , "ozone" , "pact" , "paddle" , "page" , "pair" , "palace" , "palm" , "panda" , "panel" , "panic" , "panther" , "paper" , "parade" , "parent" , "park" , "parrot" , "party" , "pass" , "patch" , "path" ,
"patient" , "patrol" , "pattern" , "pause" , "pave" , "payment" , "peace" , "peanut" , "pear" , "peasant" , "pelican" , "pen" , "penalty" , "pencil" , "people" , "pepper" , "perfect" , "permit" , "person" , "pet" , "phone" , "photo" , "phrase" ,
"physical" , "piano" , "picnic" , "picture" , "piece" , "pig" , "pigeon" , "pill" , "pilot" , "pink" , "pioneer" , "pipe" , "pistol" , "pitch" , "pizza" , "place" , "planet" , "plastic" , "plate" , "play" , "please" , "pledge" , "pluck" , "plug" ,
"plunge" , "poem" , "poet" , "point" , "polar" , "pole" , "police" , "pond" , "pony" , "pool" , "popular" , "portion" , "position" , "possible" , "post" , "potato" , "pottery" , "poverty" , "powder" , "power" , "practice" , "praise" , "predict" ,
"prefer" , "prepare" , "present" , "pretty" , "prevent" , "price" , "pride" , "primary" , "print" , "priority" , "prison" , "private" , "prize" , "problem" , "process" , "produce" , "profit" , "program" , "project" , "promote" , "proof" , "property" ,
"prosper" , "protect" , "proud" , "provide" , "public" , "pudding" , "pull" , "pulp" , "pulse" , "pumpkin" , "punch" , "pupil" , "puppy" , "purchase" , "purity" , "purpose" , "purse" , "push" , "put" , "puzzle" , "pyramid" , "quality" , "quantum" ,
"quarter" , "question" , "quick" , "quit" , "quiz" , "quote" , "rabbit" , "raccoon" , "race" , "rack" , "radar" , "radio" , "rail" , "rain" , "raise" , "rally" , "ramp" , "ranch" , "random" , "range" , "rapid" , "rare" , "rate" , "rather" , "raven" ,
"raw" , "razor" , "ready" , "real" , "reason" , "rebel" , "rebuild" , "recall" , "receive" , "recipe" , "record" , "recycle" , "reduce" , "reflect" , "reform" , "refuse" , "region" , "regret" , "regular" , "reject" , "relax" , "release" , "relief" ,
"rely" , "remain" , "remember" , "remind" , "remove" , "render" , "renew" , "rent" , "reopen" , "repair" , "repeat" , "replace" , "report" , "require" , "rescue" , "resemble" , "resist" , "resource" , "response" , "result" , "retire" , "retreat" ,
"return" , "reunion" , "reveal" , "review" , "reward" , "rhythm" , "rib" , "ribbon" , "rice" , "rich" , "ride" , "ridge" , "rifle" , "right" , "rigid" , "ring" , "riot" , "ripple" , "risk" , "ritual" , "rival" , "river" , "road" , "roast" , "robot" ,
"robust" , "rocket" , "romance" , "roof" , "rookie" , "room" , "rose" , "rotate" , "rough" , "round" , "route" , "royal" , "rubber" , "rude" , "rug" , "rule" , "run" , "runway" , "rural" , "sad" , "saddle" , "sadness" , "safe" , "sail" , "salad" ,
"salmon" , "salon" , "salt" , "salute" , "same" , "sample" , "sand" , "satisfy" , "satoshi" , "sauce" , "sausage" , "save" , "say" , "scale" , "scan" , "scare" , "scatter" , "scene" , "scheme" , "school" , "science" , "scissors" , "scorpion" , "scout" ,
"scrap" , "screen" , "script" , "scrub" , "sea" , "search" , "season" , "seat" , "second" , "secret" , "section" , "security" , "seed" , "seek" , "segment" , "select" , "sell" , "seminar" , "senior" , "sense" , "sentence" , "series" , "service" ,
"session" , "settle" , "setup" , "seven" , "shadow" , "shaft" , "shallow" , "share" , "shed" , "shell" , "sheriff" , "shield" , "shift" , "shine" , "ship" , "shiver" , "shock" , "shoe" , "shoot" , "shop" , "short" , "shoulder" , "shove" , "shrimp" ,
"shrug" , "shuffle" , "shy" , "sibling" , "sick" , "side" , "siege" , "sight" , "sign" , "silent" , "silk" , "silly" , "silver" , "similar" , "simple" , "since" , "sing" , "siren" , "sister" , "situate" , "six" , "size" , "skate" , "sketch" , "ski" ,
"skill" , "skin" , "skirt" , "skull" , "slab" , "slam" , "sleep" , "slender" , "slice" , "slide" , "slight" , "slim" , "slogan" , "slot" , "slow" , "slush" , "small" , "smart" , "smile" , "smoke" , "smooth" , "snack" , "snake" , "snap" , "sniff" ,
"snow" , "soap" , "soccer" , "social" , "sock" , "soda" , "soft" , "solar" , "soldier" , "solid" , "solution" , "solve" , "someone" , "song" , "soon" , "sorry" , "sort" , "soul" , "sound" , "soup" , "source" , "south" , "space" , "spare" , "spatial" ,
"spawn" , "speak" , "special" , "speed" , "spell" , "spend" , "sphere" , "spice" , "spider" , "spike" , "spin" , "spirit" , "split" , "spoil" , "sponsor" , "spoon" , "sport" , "spot" , "spray" , "spread" , "spring" , "spy" , "square" , "squeeze" ,
"squirrel" , "stable" , "stadium" , "staff" , "stage" , "stairs" , "stamp" , "stand" , "start" , "state" , "stay" , "steak" , "steel" , "stem" , "step" , "stereo" , "stick" , "still" , "sting" , "stock" , "stomach" , "stone" , "stool" , "story" ,
"stove" , "strategy" , "street" , "strike" , "strong" , "struggle" , "student" , "stuff" , "stumble" , "style" , "subject" , "submit" , "subway" , "success" , "such" , "sudden" , "suffer" , "sugar" , "suggest" , "suit" , "summer" , "sun" , "sunny" ,
"sunset" , "super" , "supply" , "supreme" , "sure" , "surface" , "surge" , "surprise" , "surround" , "survey" , "suspect" , "sustain" , "swallow" , "swamp" , "swap" , "swarm" , "swear" , "sweet" , "swift" , "swim" , "swing" , "switch" , "sword" ,
"symbol" , "symptom" , "syrup" , "system" , "table" , "tackle" , "tag" , "tail" , "talent" , "talk" , "tank" , "tape" , "target" , "task" , "taste" , "tattoo" , "taxi" , "teach" , "team" , "tell" , "ten" , "tenant" , "tennis" , "tent" , "term" ,
"test" , "text" , "thank" , "that" , "theme" , "then" , "theory" , "there" , "they" , "thing" , "this" , "thought" , "three" , "thrive" , "throw" , "thumb" , "thunder" , "ticket" , "tide" , "tiger" , "tilt" , "timber" , "time" , "tiny" , "tip" ,
"tired" , "tissue" , "title" , "toast" , "tobacco" , "today" , "toddler" , "toe" , "together" , "toilet" , "token" , "tomato" , "tomorrow" , "tone" , "tongue" , "tonight" , "tool" , "tooth" , "top" , "topic" , "topple" , "torch" , "tornado" ,
"tortoise" , "toss" , "total" , "tourist" , "toward" , "tower" , "town" , "toy" , "track" , "trade" , "traffic" , "tragic" , "train" , "transfer" , "trap" , "trash" , "travel" , "tray" , "treat" , "tree" , "trend" , "trial" , "tribe" , "trick" ,
"trigger" , "trim" , "trip" , "trophy" , "trouble" , "truck" , "true" , "truly" , "trumpet" , "trust" , "truth" , "try" , "tube" , "tuition" , "tumble" , "tuna" , "tunnel" , "turkey" , "turn" , "turtle" , "twelve" , "twenty" , "twice" , "twin" ,
"twist" , "two" , "type" , "typical" , "ugly" , "umbrella" , "unable" , "unaware" , "uncle" , "uncover" , "under" , "undo" , "unfair" , "unfold" , "unhappy" , "uniform" , "unique" , "unit" , "universe" , "unknown" , "unlock" , "until" , "unusual" ,
"unveil" , "update" , "upgrade" , "uphold" , "upon" , "upper" , "upset" , "urban" , "urge" , "usage" , "use" , "used" , "useful" , "useless" , "usual" , "utility" , "vacant" , "vacuum" , "vague" , "valid" , "valley" , "valve" , "van" , "vanish" ,
"vapor" , "various" , "vast" , "vault" , "vehicle" , "velvet" , "vendor" , "venture" , "venue" , "verb" , "verify" , "version" , "very" , "vessel" , "veteran" , "viable" , "vibrant" , "vicious" , "victory" , "video" , "view" , "village" , "vintage" ,
"violin" , "virtual" , "virus" , "visa" , "visit" , "visual" , "vital" , "vivid" , "vocal" , "voice" , "void" , "volcano" , "volume" , "vote" , "voyage" , "wage" , "wagon" , "wait" , "walk" , "wall" , "walnut" , "want" , "warfare" , "warm" , "warrior" ,
"wash" , "wasp" , "waste" , "water" , "wave" , "way" , "wealth" , "weapon" , "wear" , "weasel" , "weather" , "web" , "wedding" , "weekend" , "weird" , "welcome" , "west" , "wet" , "whale" , "what" , "wheat" , "wheel" , "when" , "where" , "whip" , "whisper" ,
"wide" , "width" , "wife" , "wild" , "will" , "win" , "window" , "wine" , "wing" , "wink" , "winner" , "winter" , "wire" , "wisdom" , "wise" , "wish" , "witness" , "wolf" , "woman" , "wonder" , "wood" , "wool" , "word" , "work" , "world" , "worry" , "worth" ,
"wrap" , "wreck" , "wrestle" , "wrist" , "write" , "wrong" , "yard" , "year" , "yellow" , "you" , "young" , "youth" , "zebra" , "zero" , "zone" , "zoo" };