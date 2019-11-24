solution "steamworks4j"
	configurations { "ReleaseDLL" }

	buildoptions {
		"-std=c++0x",
		"-Wall",
		"-mmacosx-version-min=10.9"
	}

	includedirs {
		"../java-wrapper/src/main/native/include/jni",
		"../java-wrapper/src/main/native/include/jni/mac",
		"../sdk/public/steam",
		"/System/Library/Frameworks/JavaVM.framework/Headers"
	}

	defines {
		"NDEBUG",
		"MACOSX"
	}

	flags {
		"Optimize"
	}

	linkoptions {
		"-framework CoreFoundation",
		"-mmacosx-version-min=10.9"
	}

	platforms {
		"x64"
	}

	project "steamworks4j"

		kind "SharedLib"
		language "C++"

		files {
			"../java-wrapper/src/main/native/**.cpp"
		}

		includedirs {
			"../java-wrapper/src/main/native"
		}

		libdirs {
			"../sdk/redistributable_bin/osx"
		}

		links {
			"steam_api"
		}

	project "steamworks4j-server"

		kind "SharedLib"
		language "C++"

		files {
			"../server/src/main/native/**.cpp"
		}

		excludes {
			"../server/src/main/native/**EncryptedAppTicket*.cpp"
		}

		includedirs {
			"../server/src/main/native"
		}

		libdirs {
			"../sdk/redistributable_bin/osx"
		}

		links {
		    "steam_api"
		}

	project "steamworks4j-encryptedappticket"

		kind "SharedLib"
		language "C++"

		files {
			"../server/src/main/native/**EncryptedAppTicket*.cpp"
		}

		includedirs {
			"../server/src/main/native"
		}

		libdirs {
			"../sdk/public/steam/lib/osx"
		}

		links {
			"sdkencryptedappticket"
		}
