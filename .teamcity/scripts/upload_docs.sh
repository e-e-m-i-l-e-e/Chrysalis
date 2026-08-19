#!/usr/bin/env bash
set -ex

BUILD_TYPE="${1:?Build type is required}"

cd "$OUTPUT_DIR"
tar -czvf documentation.tar.gz docs

curl                                                                                                                   \
  --fail-with-body                                                                                                     \
  -X POST                                                                                                              \
  -H "Authorization: Bearer $FILEBROWSER_API_KEY"                                                                      \
  --data-binary @documentation.tar.gz                                                                                  \
  "https://filebrowser.lab.eemilee.me/api/resources?path=%2Ftemp%2Fdocumentation.tar.gz&source=srv&override=true"

curl                                                                                                                   \
  --fail-with-body                                                                                                     \
  -X POST                                                                                                              \
  -H "Authorization: Bearer $FILEBROWSER_API_KEY"                                                                      \
  -H "Content-Type: application/json"                                                                                  \
  -d '{
        "fromSource": "srv",
        "path": "/temp/documentation.tar.gz",
        "destination": "/static/chrysalis",
        "deleteAfter": true
      }'                                                                                                               \
  "https://filebrowser.lab.eemilee.me/api/resources/unarchive"