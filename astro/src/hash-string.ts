export function hashString(str?: string): number {
    if (!str) return 0;
    if (str.length === 0) return 0;
    let hash = 0, i: number, chr: number;
    for (i = 0; i < str.length; i++) {
        chr = str.charCodeAt(i);
        hash = ((hash << 5) - hash) + chr;
        hash |= 0; // Convert to 32bit integer
    }
    return hash;
}
