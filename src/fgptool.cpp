// ReSharper disable CppDeclarationHidesUncapturedLocal
// ReSharper disable CppParameterMayBeConst
// ReSharper disable CppRedundantQualifier

#include <filesystem>
#include <format>
#include <iostream>
#include <set>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

#include <argparse/argparse.hpp>
#include <kvpp/KV1.h>
#include <sourcepp/FS.h>
#include <sourcepp/String.h>
#include <vpkpp/format/FGP.h>

#include "config.h"

using namespace sourcepp;
using namespace vpkpp;

namespace {

void extract(const std::vector<std::string>& inputPaths) {
	static std::unordered_map<uint32_t, std::set<std::string>> foundPaths;

	static constexpr auto addPath = [](const std::string& path) {
		static constexpr auto addPathInternal = [](const std::string& path) {
			static constexpr auto addPathInternalInternal = [](const std::string& path) {
				if (const auto hash = FGP::hashFilePath(path); !foundPaths.contains(hash)) {
					foundPaths.emplace(hash, std::set{path});
				} else {
					foundPaths.at(hash).insert(path);
				}
			};
			addPathInternalInternal(path);
			addPathInternalInternal(path + ".qpre");

			if (const auto index = path.rfind(".360"); index != std::string::npos) {
				std::string ps3path = path;

				ps3path.replace(index, 4, ".ps3");
				addPathInternalInternal(ps3path);
				addPathInternalInternal(ps3path + ".qpre");

				ps3path.replace(index, 4, "");
				addPathInternalInternal(ps3path);
				addPathInternalInternal(ps3path + ".qpre");
			}
		};

		addPathInternal(path);

		// Add EA language files
		if (path.starts_with("resource/portal_") && path.ends_with(".txt")) {
			addPathInternal("resource/ea_" + path.substr(16));
		}

		// Wishful thinking
		if (path.ends_with(".dll")) {
			addPathInternal(std::filesystem::path{path}.replace_extension(".pdb").string());
			addPathInternal(std::filesystem::path{path}.replace_extension(".dbg").string());
		}
	};

	// Probably don't exist
	//addPath("__preload_section.pre");
	//addPath("lightdata.swp");
	//addPath("makereslists.txt");
	//addPath("makereslists_xbox.txt");
	//addPath("resource/engine.lst");
	//addPath("resource/undelete.lst");
	//addPath("materials/allow1024.txt");

	// AppChooser sounds are laid out in the root directory lol
	addPath("ui/buttonclick.wav");
	addPath("ui/buttonclickrelease.wav");
	addPath("player/suit_denydevice.wav");

	for (int i = 0; i <= 20; i++) {
		addPath(std::format("materials/console/background{}.vmt", i));
		addPath(std::format("materials/console/background{}.vtf", i));
		addPath(std::format("materials/console/background{}_widescreen.vmt", i)); // WRONG?
		addPath(std::format("materials/console/background{}_widescreen.vtf", i));
	}
	addPath("materials/dev/bloomadd_ps3.vmt");
	addPath("materials/models/weapons/v_models/v_hands/v_hands.vmt");
	addPath("materials/models/weapons/v_models/v_hands/v_hands.vtf");
	for (int i = 0; i <= 20; i++) {
		addPath(std::format("materials/vgui/chapters/xbox/chapter{}.vmt", i));
		addPath(std::format("materials/vgui/chapters/xbox/chapter{}.vtf", i));
		addPath(std::format("materials/vgui/chapters/xbox/chapter{}a.vmt", i));
		addPath(std::format("materials/vgui/chapters/xbox/chapter{}a.vtf", i));
		addPath(std::format("materials/vgui/chapters/xbox/chapter{}b.vmt", i));
		addPath(std::format("materials/vgui/chapters/xbox/chapter{}b.vtf", i));
		addPath(std::format("materials/vgui/chapters/chapter{}.vmt", i));
		addPath(std::format("materials/vgui/chapters/chapter{}.vtf", i));
		addPath(std::format("materials/vgui/chapters/chapter{}a.vmt", i));
		addPath(std::format("materials/vgui/chapters/chapter{}a.vtf", i));
		addPath(std::format("materials/vgui/chapters/chapter{}b.vmt", i));
		addPath(std::format("materials/vgui/chapters/chapter{}b.vtf", i));
	}
	for (int i = 0; i <= 33; i++) {
		addPath(std::format("materials/vgui/anims/loading_64_{}.vmt", i));
		addPath(std::format("materials/vgui/anims/loading_64_{}.vtf", i));
	}
	addPath("resource/dialogue/creategame.res");
	addPath("resource/dialogue/feslgamebrowserdialogue.res");
	addPath("resource/dialogue/ps3playgroupsettingsdialog.res");
	addPath("resource/popups/eaonline_connecting.res");
	addPath("resource/popups/eaonline_connectionfailed.res");
	addPath("resource/popups/eaonline_connectingtogame.res");
	addPath("resource/popups/eaonline_connectiontogamefailed.res");
	addPath("resource/popups/eaonline_noserversfound.res");
	addPath("resource/popups/eaonline_queued.res");
	addPath("resource/popups/eaonline_registering.res");
	addPath("resource/popups/eaonline_registrationfailed.res");
	addPath("resource/ps3/ps3playerlistdialog.res");
	addPath("resource/ps3/ps3playgroupinvites.res");
	addPath("resource/ui/xboxdialogs.res");
	addPath("resource/optionssubcontroller.res");
	addPath("resource/optionssubps3.res");
	addPath("resource/optionssubps3audio.res");
	addPath("resource/optionssubps3controller.res");
	addPath("resource/optionssubps3difficulty.res");
	addPath("resource/optionssubps3video.res");
	addPath("resource/playnow.txt");
	addPath("resource/popups/eaonline_registeringgame.res");
	addPath("resource/popups/eaonline_retrievingserverlist.res");
	addPath("resource/popups/popup.res");
	addPath("resource/ps3/ps3createserver.res");
	addPath("resource/ps3/ps3findserver.res");
	addPath("resource/ps3/ps3disconnectinplaygroup.res");
	addPath("resource/ps3/ps3matchmaker.res");
	addPath("resource/ps3newgamedialog.res");
	addPath("resource/ps3/ps3optionscontroller.res");
	addPath("resource/ps3/ps3popup.res");
	addPath("resource/ps3/ps3queueforgame.res");
	addPath("scripts/options.txt");
	addPath("scripts/mod_options.txt");
	for (int i = 0; i <= 6; i++) {
		for (int j = 0; j <= 4; j++) {
			addPath(std::format("sound/vo/aperture_ai/bonus{:02}_part{}.wav", i, j));
		}
	}

	// Fonts
	for (std::string font : {
		"cour",
		"verdana",
		"arial",
		"tahoma",
		"trebuc",
		"HALFLIFE2",
		"marlett",
		"HL2crosshairs",
		"lucon",
		"impact",
		"HL2EP1",
		"HL2MP",
		"tf",
		"tfd",
		"TFlogo",
		"HL2EP2",
		"HL2PS3",
		"CompactaBlack",
		"TF2",
		"TF2Build",
		"TF2secondary",
		"TF2Professor",
	}) {
		string::toLower(font);
		addPath("resource/" + font + ".ttf");
	}

	for (const auto& root : inputPaths) {
		for (const auto& it : std::filesystem::recursive_directory_iterator{root}) {
			if (!it.is_regular_file()) {
				continue;
			}

			if (it.path().extension() == ".bsp") {
				addPath("reslists_xbox/" + it.path().stem().string() + ".lst");
				addPath("reslists_xbox/" + it.path().stem().string() + "_exclude.lst");
				continue;
			}

			if (it.path().extension() == ".vpk" || it.path().extension() == ".zip") {
				const auto vpkPath = it.path().string();
				if (vpkPath.length() < 7 || string::matches(vpkPath.substr(vpkPath.length() - 7), "%d%d%d.vpk")) {
					continue;
				}
				const auto vpk = PackFile::open(vpkPath);
				if (!vpk) {
					continue;
				}
				vpk->runForAllEntries([](const std::string& path, const Entry&) { addPath(path); });
				continue;
			}

			auto filePath = std::filesystem::relative(it.path(), root).string();
			string::normalizeSlashes(filePath);
			string::toLower(filePath);
			addPath(filePath);
		}
	}
	std::cout << "Found " << foundPaths.size() << " paths." << std::endl;

	kvpp::KV1Writer kv;
	for (const auto& [hash, paths] : foundPaths) {
		if (paths.size() > 1) {
			std::cerr << std::format("Hash {:08x} ", hash) << "has multiple candidates! Using first one..." << std::endl;
			for (const auto& path : paths) {
				std::cerr << "- " << path << std::endl;
			}
		}
		const auto hashHex = std::format("{:08x}", hash);
		kv.addChild(std::string{hashHex[6]} + hashHex[7] + hashHex[4] + hashHex[5] + hashHex[2] + hashHex[3] + hashHex[0] + hashHex[1], *paths.begin());
	}
	kv.bake("mappings.kv");
	std::cout << "Created mappings.kv successfully with " << kv.getChildCount() << " hashes." << std::endl;
}

void crack(const std::string& inputPath) {
	const auto fgp = FGP::open(inputPath);
	if (!fgp) {
		std::cerr << "Can't open file \"" << inputPath << "\" as FGP!" << std::endl;
		return;
	}

	const kvpp::KV1 kv{fs::readFileText("mappings.kv")};

	const uint32_t total = fgp->getEntryCount();
	uint32_t found = 0, existed = 0;

	std::vector<std::string> fgpCRCs;
	fgp->runForAllEntries([&found, &existed, &fgpCRCs](const std::string& path, const Entry&) {
		if (path.starts_with("__hashed__/")) {
			fgpCRCs.push_back(path.substr(11));
		} else {
			found++;
			existed++;
		}
	});
	for (const auto& crc : fgpCRCs) {
		if (!kv[crc].isInvalid()) {
			fgp->renameEntry("__hashed__/" + crc, std::string{kv[crc].getValue()});
			found++;
		}
	}
	fgp->bake("", {}, nullptr);

	std::cout << (found / static_cast<double>(total) * 100) << "% hashes identified (" << ((found - existed) / static_cast<double>(total) * 100)  << "% new) for " << std::filesystem::path{inputPath}.filename().string() << std::endl;
}

void meta(const std::string& inputPath) {
	const auto fgp = FGP::open(inputPath);
	if (!fgp) {
		std::cerr << "Can't open file \"" << inputPath << "\" as FGP!" << std::endl;
		return;
	}
	std::cout << fgp->getFilename() << std::endl;
	std::cout << "\tFile count: " << fgp->getEntryCount() << std::endl;

	const uint32_t total = fgp->getEntryCount();
	uint32_t existed = 0;
	fgp->runForAllEntries([&existed](const std::string& path, const Entry&) {
		existed += !path.starts_with("__hashed__/");
	});
	std::cout << "\tMissing hashes: " << (total - existed) << " (" << ((total - existed) / static_cast<double>(total) * 100) << "%)" << std::endl;

	std::cout << "\tLoading screen path: " << dynamic_cast<FGP&>(*fgp).getLoadingScreenFilePath() << std::endl;
}

void dump(const std::string& inputPath) {
	const auto fgp = FGP::open(inputPath);
	if (!fgp) {
		std::cerr << "Can't open file \"" << inputPath << "\" as FGP!" << std::endl;
		return;
	}
	if (const auto outputPath = std::filesystem::path{fgp->getFilepath()}.parent_path().string(); !fgp->extractAll(outputPath)) {
		std::cerr << "Failed to extract some files to \"" << outputPath << "\"!" << std::endl;
	} else {
		std::cout << "Extracted " << fgp->getFilename() << " to \"" << (std::filesystem::path{outputPath} / fgp->getFilestem()).string() << "\"." << std::endl;
	}
}

void test() {
	std::string path;
	while (std::getline(std::cin, path)) {
		if (path == "exit" || path == "quit") {
			break;
		}
		string::normalizeSlashes(path, true);
		const auto hashHex = std::format("{:08x}", FGP::hashFilePath(path));
		std::cout << '\t' << (std::string{hashHex[6]} + hashHex[7] + hashHex[4] + hashHex[5] + hashHex[2] + hashHex[3] + hashHex[0] + hashHex[1]) << '\n' << std::endl;
	}
}

} // namespace

int main(int argc, const char* const argv[]) {
	argparse::ArgumentParser cli{PROJECT_NAME, PROJECT_VERSION, argparse::default_arguments::help};

	std::vector<std::string> inputPaths;
	cli.add_argument("input").metavar("PATH").help("The input path(s).").remaining().store_into(inputPaths);

	std::string mode = "CRACK";
	cli.add_argument("-m", "--mode").metavar("MODE").help("The active mode. Can be EXTRACT, CRACK, META, DUMP, or TEST.").choices("EXTRACT", "CRACK", "META", "DUMP", "TEST").default_value(mode).store_into(mode);

	cli.add_epilog(
		PROJECT_NAME " — version v" PROJECT_VERSION " — created by " PROJECT_ORGANIZATION_NAME " — licensed under MIT\n"
		"Want to report a bug or request a feature? Make an issue at " PROJECT_HOMEPAGE_URL "/issues"
	);

	try {
		cli.parse_args(argc, argv);

		if (mode == "TEST") {
			::test();
			return EXIT_SUCCESS;
		}

		if (inputPaths.empty()) {
			throw std::runtime_error{"No input path(s) provided!"};
		}

		if (mode == "EXTRACT") {
			::extract(inputPaths);
		} else {
			for (const auto& inputPath : inputPaths) {
				// Check input path is valid
				if (!std::filesystem::exists(inputPath)) {
					throw std::runtime_error{"Input path \"" + inputPath + "\" does not exist!"};
				}
				if (std::filesystem::is_directory(inputPath)) {
					for (const auto& entry : std::filesystem::directory_iterator(inputPath)) {
						if (entry.is_regular_file() && entry.path().extension().string() == ".GRP") {
							if (mode == "CRACK") {
								::crack(entry.path().string());
							} else if (mode == "META") {
								::meta(entry.path().string());
							} else {
								::dump(entry.path().string());
							}
						}
					}
				} else if (mode == "CRACK") {
					::crack(inputPath);
				} else if (mode == "META") {
					::meta(inputPath);
				} else {
					::dump(inputPath);
				}
			}
		}
	} catch (const std::exception& e) {
		if (argc > 1) {
			std::cerr << e.what() << std::endl;
		} else {
			std::cout << cli << std::endl;
		}
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
