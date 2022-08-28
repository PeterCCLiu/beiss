const { expect } = require("chai");

describe("MyToken contract", function () {

  let myToken;
  let myTokenContract;
  let owner;
  let addr1;
  let addr2;
  let addrs;

  beforeEach(async function () {

    myToken = await ethers.getContractFactory("MyToken");

    [owner, addr1, addr2, ...addrs] = await ethers.getSigners();

    myTokenContract = await myToken.deploy();
  });

  describe("Deployment", function () {
    it("Should set the right owner", async function () {
      expect(await myTokenContract.owner()).to.equal(owner.address);
    });

    it("Should assign the total supply of tokens to the owner", async function () {
      const ownerBalance = await myTokenContract.balanceOf(owner.address);
      expect(await myTokenContract.totalSupply()).to.equal(ownerBalance);
    });
  });

  describe("Transactions", function () {
    it("Should transfer tokens between accounts", async function () {
      await myTokenContract.transfer(addr1.address, 50);
      const addr1Balance = await myTokenContract.balanceOf(addr1.address);
      expect(addr1Balance).to.equal(50);

      await myTokenContract.connect(addr1).transfer(addr2.address, 50);
      const addr2Balance = await myTokenContract.balanceOf(addr2.address);
      expect(addr2Balance).to.equal(50);
    });

    it("Should fail if sender doesn’t have enough tokens", async function () {
      const initialOwnerBalance = await myTokenContract.balanceOf(owner.address);

      await expect(
          myTokenContract.connect(addr1).transfer(owner.address, 1)
      ).to.be.revertedWith("Not enough tokens");

      expect(await myTokenContract.balanceOf(owner.address)).to.equal(
          initialOwnerBalance
      );
    });

    it("Should update balances after transfers", async function () {
      const initialOwnerBalance = await myTokenContract.balanceOf(owner.address);

      await myTokenContract.transfer(addr1.address, 100);

      await myTokenContract.transfer(addr2.address, 50);

      const finalOwnerBalance = await myTokenContract.balanceOf(owner.address);
      expect(finalOwnerBalance).to.equal(initialOwnerBalance - 150);

      const addr1Balance = await myTokenContract.balanceOf(addr1.address);
      expect(addr1Balance).to.equal(100);

      const addr2Balance = await myTokenContract.balanceOf(addr2.address);
      expect(addr2Balance).to.equal(50);
    });
  });
});