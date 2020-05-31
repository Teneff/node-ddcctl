"use strict";
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
const src_1 = __importDefault(require("../src"));
console.log(src_1.default.mainn());
src_1.default.addEventListener("brightnesschange", (e) => {
    console.log("brightness", e);
});
while (true) { }
