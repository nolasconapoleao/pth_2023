// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;

import "@openzeppelin/contracts/token/ERC721/ERC721.sol";
import "@openzeppelin/contracts/access/Ownable.sol";

contract NFTVendingMachine is Ownable {
    ERC721 public nftContract;
    uint256 public nftPrice;
    
    // Mapping to keep track of whether an address has already purchased
    mapping(address => bool) public hasPurchased;

    event NFTPurchased(address indexed buyer, uint256 tokenId);

    constructor(
        address _nftContract,
        uint256 _nftPrice
    ) {
        nftContract = ERC721(_nftContract);
        nftPrice = _nftPrice;
    }

    function purchaseNFT() external payable {
        require(!hasPurchased[msg.sender], "You have already purchased an NFT.");
        
        require(msg.value >= nftPrice, "Insufficient ETH sent.");
        
        // Mint and transfer the NFT to the sender
        uint256 tokenId = nftContract.totalSupply() + 1; // Replace this with your NFT minting logic
        nftContract.mint(msg.sender, tokenId); // Replace with your mint function
        
        // Mark the sender as having purchased
        hasPurchased[msg.sender] = true;

        // Emit the purchase event
        emit NFTPurchased(msg.sender, tokenId);
    }
    
    function setNFTPrice(uint256 _newPrice) external onlyOwner {
        nftPrice = _newPrice;
    }
    
    function withdrawPayments() external onlyOwner {
        payable(owner()).transfer(address(this).balance);
    }
}
