async function main() {
  const VIPMembership = await ethers.getContractFactory("VIPMembership");
  const vip_membership = await VIPMembership.deploy(15000);
  console.log("Contract Deployed to Address:", vip_membership.address);
}

main()
  .then(() => process.exit(0))
  .catch(error => {
    console.error(error);
    process.exit(1);
  });
