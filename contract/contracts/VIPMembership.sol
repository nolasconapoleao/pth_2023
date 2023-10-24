// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;

contract VIPMembership {
    address public owner;
    uint256 public baseMembershipPrice;
    mapping(address => bool) public isVipMember;
    mapping(address => uint8) public tierLevels;

    event MembershipPurchased(address indexed member, uint256 amount, uint8 tier);
    event MembershipRevoked(address indexed member);

    constructor(uint256 _baseMembershipPrice) {
        owner = msg.sender;
        baseMembershipPrice = _baseMembershipPrice;
    }

    modifier onlyOwner() {
        require(msg.sender == owner, "Only the owner can perform this action");
        _;
    }

    function purchaseMembership() external payable {
        uint8 tier = getTierLevel(msg.value);
        uint256 price = calculateMembershipPrice(tier);

        require(msg.value >= price, "Insufficient payment");
        require(!isVipMember[msg.sender], "You are already a VIP member");

        isVipMember[msg.sender] = true;
        tierLevels[msg.sender] = tier;

        emit MembershipPurchased(msg.sender, msg.value, tier);
    }

    function removeMember(address memberAddress) external onlyOwner {
        require(isVipMember[memberAddress], "Address is not a VIP member");

        isVipMember[memberAddress] = false;
        delete tierLevels[memberAddress];

        emit MembershipRevoked(memberAddress);
    }

    function addMember(address memberAddress, uint8 tier) external onlyOwner {
        require(!isVipMember[memberAddress], "Address is already a VIP member");
        require(tier > 0, "Tier should be greater than 0");

        isVipMember[memberAddress] = true;
        tierLevels[memberAddress] = tier;
        
        emit MembershipPurchased(memberAddress, 0, tier);
    }

    function getTierLevel(uint256 amount) public view returns (uint8) {
        uint8 tier = 0;
        uint256 price = baseMembershipPrice;

        while (amount >= price) {
            tier++;
            price = calculateMembershipPrice(tier);
        }

        return tier;
    }

    function calculateMembershipPrice(uint8 tier) public view returns (uint256) {
        return baseMembershipPrice * (2**tier);
    }

    function isAddressVIP(address memberAddress) public view returns (bool) {
        return isVipMember[memberAddress];
    }

    function setMembershipPrice(uint256 _baseMembershipPrice) external onlyOwner {
        baseMembershipPrice = _baseMembershipPrice;
    }

    function getBaseMembershipPrice() external view returns (uint256) {
        return baseMembershipPrice;
    }

    function withdrawBalance() external onlyOwner {
        payable(owner).transfer(address(this).balance);
    }
}
