require("@nomiclabs/hardhat-waffle");

const PRIVATE_KEY = "ac0974bec39a17e36ba4a6b4d238ff944bacb478cbed5efcae784d7bf4f2ff80"

module.exports = {
    solidity: "0.8.9",
    networks: {
        myTest: {
            url: `http://127.0.0.1:8545`,
            accounts: [`0x${PRIVATE_KEY}`]
        }
    }
};
