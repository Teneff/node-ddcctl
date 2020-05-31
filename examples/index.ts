import nddcctl from "../src";

console.log(nddcctl.mainn());

nddcctl.addEventListener("brightnesschange", (e: any) => {
  console.log("brightness", e);
});

while(true){}