import bindings from "bindings";

type Size = {
  width: number;
  height: number;
};

export interface Display {
  id: number;
  displayScale: number;
  rotation: number;
  size: {
    physical: Size;
    pixel: Size;
  };
}

export interface BuiltInDisplay extends Display {
  isBuiltIn: true;
}

export interface ExternalDisplay extends Display {
  isBuiltIn: false;
  setBrightness: (brightness: number) => Promise<boolean>;
}

export interface NodeDDCTL {
  mainn: () => (BuiltInDisplay | ExternalDisplay)[];
  addEventListener: (eventType: string, callback: (e: any) => void) => void;
}

const nddcctl: NodeDDCTL = bindings("nddcctl");

export default nddcctl;
