#!/usr/bin/env python3
"""
Download Advent of Code 2016 puzzle inputs.

Usage:
    python aoc2016_download.py --session YOUR_SESSION_COOKIE

How to get your session cookie:
  1. Log in to https://adventofcode.com
  2. Open DevTools → Application (Chrome) or Storage (Firefox) → Cookies
  3. Copy the value of the cookie named "session"

Files are saved as day-1.txt … day-25.txt in ./aoc2016/ (or --out DIR).
Already-existing files are skipped.
"""

import argparse
import os
import sys
import time
from pathlib import Path

try:
    import requests
except ImportError:
    sys.exit("❌  'requests' is not installed. Run:  pip install requests")

YEAR = 2016
DELAY = 1.0  # seconds between requests – be kind to AoC servers


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--session", metavar="COOKIE", help="AoC session cookie")
    parser.add_argument("--out", metavar="DIR", default="aoc2016", help="Output directory (default: ./aoc2016)")
    args = parser.parse_args()

    session = args.session or os.environ.get("AOC_SESSION", "")
    if not session:
        sys.exit("❌  No session cookie. Pass --session or set AOC_SESSION.")
    if session.startswith("session="):
        session = session[len("session="):]

    out_dir = Path(args.out)
    out_dir.mkdir(parents=True, exist_ok=True)

    http = requests.Session()
    http.cookies.set("session", session.strip(), domain="adventofcode.com")
    http.headers["User-Agent"] = "personal-aoc-downloader"

    print(f"📂 Saving to: {out_dir.resolve()}\n")

    for day in range(1, 26):
        path = out_dir / f"day-{day}.txt"
        if path.exists():
            print(f"  day {day:02d} – already exists, skipping")
            continue

        url = f"https://adventofcode.com/{YEAR}/day/{day}/input"
        try:
            resp = http.get(url, timeout=15)
            resp.raise_for_status()
            path.write_text(resp.text, encoding="utf-8")
            print(f"  day {day:02d} – saved ({resp.text.count(chr(10))} lines)")
        except requests.HTTPError as exc:
            print(f"  day {day:02d} – HTTP {exc.response.status_code}, skipping")

        time.sleep(DELAY)

    print(f"\n✅  Done! Files saved to {out_dir}/")


if __name__ == "__main__":
    main()
