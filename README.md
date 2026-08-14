[![Discord community](https://img.shields.io/badge/Discord-%235865F2.svg?style=for-the-badge&logo=discord&logoColor=white)](https://discord.gg/B3qJBE3M9W) [![Satisfactory mod portal](https://img.shields.io/badge/dynamic/json?url=https%3A%2F%2Fapi.ficsit.app%2Fv1%2Fmod%2FMODID&query=data.downloads&suffix=%20downloads&style=for-the-badge&color=orange&label=ficsit.app&labelColor=rgb(111,148,173))](https://ficsit.app/mod/FluidMiner) ![Multiplayer supported](https://img.shields.io/badge/Multiplayer-Supported-green?style=for-the-badge) [![GitHub issues: bugs](https://img.shields.io/github/issues/QuingKhaos/sf-FluidMiner/bug?label=Bug%20Reports&style=for-the-badge&logo=github)](https://github.com/QuingKhaos/sf-FluidMiner/issues?q=is%3Aissue%20state%3Aopen%20label%3Abug) [![GitHub pull requests](https://img.shields.io/github/issues-pr/QuingKhaos/sf-FluidMiner?label=Pull%20Requests&style=for-the-badge&logo=github)](https://github.com/QuingKhaos/sf-FluidMiner/pulls)

# Fluid Miner

Three tiers of miners that can use fluid to extract ores. This mod does nothing on its own, except for adding the Fluid Miner, which are unlocked together with their respective regular miner of the same tier.

## For modders

Create a new resource node BP based on `BP_KhaosFluidMiningResourceNode` and set the Fluid Miner properties. Example:

![Example node](https://github.com/QuingKhaos/sf-FluidMiner/blob/1.x/.github/images/BP_TitaniumOre_Node.png?raw=true)

That's it. Now only fluid miners can extract from this node, requiring the amount of the defined mining fluid.

![Example miner](https://github.com/QuingKhaos/sf-FluidMiner/blob/1.x/.github/images/Build_FluidMinerMk1.png?raw=true)

## Credits

- Based on [AlkaLib](https://ficsit.app/mod/AlkaLib) by [AniViRus Productions](https://ficsit.app/user/EQXUyJ73G7VxfE).

## License

This mod is licensed under the [LGPLv3](https://www.gnu.org/licenses/lgpl-3.0.html), unlike my other mods which are mostly licensed under the GPLv3. Mods that are using Fluid Miner are not required to be open source, nor are they required to be licensed under the LGPLv3. However, if you modify this mod and distribute the modified version, you must also distribute the source code of your modified version under the LGPLv3.
