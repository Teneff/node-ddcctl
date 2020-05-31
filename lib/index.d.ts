declare type Size = {
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
    on: (eventType: string, callback: (e: any) => void) => void;
}
declare const nddcctl: NodeDDCTL;
export default nddcctl;
