import pandas as pd
import glob
import os

INPUT_FOLDER = "bom_inputs"   # ide rakd a CSV fájlokat
OUTPUT_FILE = "MASTER_BOM_OUTPUT.xlsx"

def load_bom_csv(path):
    """Beolvas egy KiCad BOM CSV-t automatikusan felismerve a ; szeparátort."""
    df = pd.read_csv(path, sep=';', quotechar='"')
    df['Source'] = os.path.basename(path)
    return df

def main():
    # CSV-k betöltése

    # A futó script könyvtára
    BASE_DIR = os.path.dirname(os.path.abspath(__file__))

    # A bom_inputs mappa abszolút elérése
    INPUT_FOLDER = os.path.join(BASE_DIR, "bom_inputs")

    # Minden CSV fájl beolvasása
    files = glob.glob(os.path.join(INPUT_FOLDER, "*.csv"))
    if not files:
        print("Nincs CSV a bom_inputs mappában.")
        return

    dfs = [load_bom_csv(f) for f in files]

    # MASTER tábla
    master = pd.concat(dfs, ignore_index=True)

    # Normalizáljuk az oszlopneveket
    master.columns = [c.strip().replace(" ", "_") for c in master.columns]

    # Egy kulcs képzése (Designation + Footprint)
    master["Key"] = (
        master["Designation"].astype(str).str.strip()
        + "_"
        + master["Footprint"].astype(str).str.strip()
    )

    # Összesített rendelési lista
    summary = (
        master.groupby("Key")["Quantity"]
        .sum()
        .reset_index()
        .sort_values("Quantity", ascending=False)
    )

    # Mentés Excelbe
    with pd.ExcelWriter(OUTPUT_FILE) as writer:
        master.to_excel(writer, sheet_name="MASTER", index=False)
        summary.to_excel(writer, sheet_name="ORDER_SUMMARY", index=False)

    print("Kész! ->", OUTPUT_FILE)


if __name__ == "__main__":
    main()
