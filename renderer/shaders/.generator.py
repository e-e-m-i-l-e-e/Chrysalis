import sys
from pathlib import Path
from collections import defaultdict

shader_dir = Path(__file__).parent
out_dir = Path(sys.argv[1])

programs = defaultdict(list)
shaders = list(shader_dir.glob("*.vert")) + list(shader_dir.glob("*.frag"))

def stage(path: Path):
    if path.suffix == ".vert":
        return "Vertex"
    if path.suffix == ".frag":
        return "Fragment"
    return "unknown"

for s in shaders:
    programs[s.stem].append(s)

for program, files in programs.items():

    out_file = out_dir / f"{program}_shaders.h"

    lines = []
    for f in files:
        lines.append(f'inline constexpr const char* {program}{stage(f)}Shader = R"glsl(')
        lines.append(f.read_text(encoding="utf-8"))
        lines.append(')glsl";\n')

    out_file.write_text("\n".join(lines), encoding="utf-8")