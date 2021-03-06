#!/bin/bash

set -e -u
source "${TEST_SRCDIR}/bin/imos-variables" || exit 1
eval "${IMOSH_INIT}"

TARGET="${TEST_SRCDIR}/src/sim/sim_main"

PROGRAM1="${TMPDIR}/program1.sh"
PROGRAM2="${TMPDIR}/program2.sh"

PHRASES=(
  -p "ei!"
  -p "ia! ia!"
  -p "r'lyeh"
  -p "necronomicon"
  -p "yogsothoth"
  -p "in his house at r'lyeh dead cthulhu waits dreaming."
  -p "yuggoth"
  -p "blue hades"
  -p "planet 10"
  -p "monkeyboy"
  -p "tsathoggua"
  -p "yoyodyne"
  -p "john bigboote"
  -p "the laundry"
  -p "cthulhu fhtagn!"
)

cat << 'EOM' > "${TMPDIR}/program1.sh"
cat << 'EOF'
[{"problemId":0,"seed":0,"solution":"ia! ia!lei!lbbbbei!aia! ia!lei!lbbbbbbbblablue hadesyuggothei!kbbablue hadesldei!dpppppr'lyehpblue hadesei!ddei!ppppkei!dei!dppblue hadesei!r'lyehpppppppr'lyehbablue hadesei!r'lyehkppdlpblue hadesei!r'lyehklpblue hadesei!ddei!pppppkklpblue hadesei!r'lyehei!kppppablue hadesei!r'lyehppppblue hadesei!r'lyehdpppblue hadeskppddpppr'lyehpppkei!kpblue hadesei!r'lyehbdei!kkkei!dppblue hadesei!ddr'lyehlpyogsothothppr'lyehddayogsothothdpppr'lyehkppplanet 10apapblue hadesei!lei!kbblapblue hadesei!r'lyehdei!dpppblue hadesei!r'lyehppblue hadesei!kei!kbblllkpblue hadesei!r'lyehlpblue hadesei!kei!kei!ppppalpplanet 10dei!pkei!dapblue hadesei!kei!kkei!kbldpblue hadesei!pppr'lyehppppkpblue hadesldei!ddalpblue hadesei!r'lyehpkpppr'lyehppblue hadesaddei!ppppr'lyehpyogsothothei!apblue hadesei!r'lyehppdlpyogsothothei!kei!kbbei!ddbaia! ia!lei!lbbbei!ablue hadesyuggothbablue hadesei!r'lyehkkppppppr'lyehkpppia! ia!lbbbbbbbei!ablue hadeskppddr'lyehpppppkei!kpyogsothothr'lyehkppblue hadesei!kei!kei!dei!apblue hadeskppddr'lyehpklpblue hadesia! ia!kkppppblue hadesei!kei!kkei!kei!ppppyogsothothr'lyehei!kpblue hadesei!r'lyehbablue hadesei!kei!kkblapblue hadesei!dblpblue hadesei!ppr'lyehkppblue hadesei!kei!kei!kpppapblue hadesei!dei!klapblue hadesei!","tag":"chokudAIver2.2.9@7451"}]
EOF
sleep 20
cat << 'EOF'
[{"problemId":0,"seed":0,"solution":"ia! ia!lei!lbbbbei!aia! ia!lei!lbbbbbbbblablue hadesyuggothei!kbbablue hadesldei!dpppppr'lyehpblue hadesei!ddei!ppppkei!dei!dppblue hadesei!r'lyehpppppppr'lyehbablue hadesei!r'lyehkppdlpblue hadesei!r'lyehklpblue hadesei!ddei!pppppkklpblue hadesei!r'lyehei!kppppablue hadesei!r'lyehppppblue hadesei!r'lyehdpppblue hadeskppddpppr'lyehpppkei!kpblue hadesei!r'lyehbdei!kkkei!dppblue hadesei!ddr'lyehlpyogsothothppr'lyehddayogsothothdpppr'lyehkppplanet 10apapblue hadesei!lei!kbblapblue hadesei!r'lyehdei!dpppblue hadesei!r'lyehppblue hadesei!kei!kbblllkpblue hadesei!r'lyehlpblue hadesei!kei!kei!ppppalpplanet 10dei!pkei!dapblue hadesei!kei!kkei!kbldpblue hadesei!pppr'lyehppppkpblue hadesldei!ddalpblue hadesei!r'lyehpkpppr'lyehppblue hadesaddei!ppppr'lyehpyogsothothei!apblue hadesei!r'lyehppdlpyogsothothei!kei!kbbei!ddbaia! ia!lei!lbbbei!ablue hadesyuggothbablue hadesei!r'lyehkkppppppr'lyehkpppia! ia!lbbbbbbbei!ablue hadeskppddr'lyehpppppkei!kpyogsothothr'lyehkppblue hadesei!kei!kei!dei!apblue hadeskppddr'lyehpklpblue hadesia! ia!kkppppblue hadesei!kei!kkei!kei!ppppyogsothothr'lyehei!kpblue hadesei!r'lyehbablue hadesei!kei!kkblapblue hadesei!dblpblue hadesei!ppr'lyehkppblue hadesei!kei!kei!kpppapblue hadesei!dei!klapblue hadesei!r'lyehkblpyogsothothei!kei!kei!kpppblue hadesei!r'lyehkpablue hadesei!ppppr'lyehbablue hadeskkei!kei!pppppr'lyehppppblue hadesei!kei!kppppr'lyehkkppblue hadesei!dei!dpppppr'lyehklpblue hadesei!r'lyehdpblue hadeskkkkppppppr'lyehldpyogsothothei!kei!pblue hadesei!dbei!kbbkpblue hadesei!r'lyehpdpblue hadesei!kei!kei!ppkpkei!papblue hadesbei!kei!dpppppr'lyehpyogsothothei!dbddbbbablue hadesei!ppddei!dei!dalpblue hadesei!kkei!kkppkei!dei!dbbaia! ia!lei!lei!pblue hadesaei!ddppppkei!dei!dpppblue hadesaei!ddppppkei!kbablue hadesei!r'lyehddpppkpblue hadesei!r'lyehlpblue hadesei!dppppppr'lyehklpblue hadesyuggothei!ddppia! ia!lei!lbei!ablue hadesei!lei!kkppppr'lyehkkpblue hadesei!r'lyehpppapblue hadesei!r'lyehei!kei!dbbablue hadesei!r'lyehkpppppppdapblue hadesei!dr'lyehei!pyogsothothei!dppapblue hadesei!r'lyehdlpblue hadeskppdr'lyehlpblue hadesei!dei!kbbdlpblue hadesei!kei!kkei!kei!dpablue hadesei!pr'lyehpblue hadesldei!ppppr'lyehddpblue hadesei!dei!pdpppr'lyehpdlpblue hadesei!pppppr'lyehkppblue hadesei!pppppr'lyehdapblue hadesei!dei!ppkei!dpppppblue hadesei!r'lyehkppappppblue hadesei!r'lyehdpblue hadesei!r'lyehppppr'lyehkppyogsothothr'lyehldpblue hadesei!lei!kkkpppr'lyehkpppblue hadesei!dei!pppr'lyehdablue hadesei!r'lyehkpblue hadesldei!dpppppppr'lyehpblue hadesei!dei!pkei!p","tag":"chokudAIver2.2.9@7451"}]
EOF
EOM

cat << 'EOM' > "${TMPDIR}/program2.sh"
cat << 'EOF'
[{"problemId":0,"seed":0,"solution":"bbei!ia! ia! ia!pbbbbei!ia! ia! ia!apr'lyehpr'lyehppr'lyehppr'lyehppdpei!","tag":"chokudAIver2.3.5Div5@12083"}]
EOF
sleep 20
cat << 'EOF'
[{"problemId":0,"seed":0,"solution":"bbei!ia! ia! ia!pbbbbei!ia! ia! ia!apr'lyehpr'lyehppr'lyehppr'lyehppdpei!pppr'lyehkei!r'lyehppr'lyehppkyoyodynedpppppppddblue hadesei!pei!ddplanet 10pmonkeyboyabdyuggoththe laundryar'lyehkkyogsothothpbbbbtsathogguabddappknecronomiconappr'lyehppr'lyehr'lyehppdei!pei!ppr'lyehpr'lyehpdappdei!pppr'lyehr'lyehr'lyehpppdpkjohn bigbootedabei!r'lyehei!kei!r'lyehbbbar'lyehkei!r'lyehr'lyehr'lyehppr'lyehkpr'lyehr'lyehr'lyehppdpr'lyehr'lyehr'lyehbakei!kkpr'lyehr'lyehr'lyehlpei!ppr'lyehei!kei!r'lyehkkppr'lyehdei!ppr'lyehr'lyehbbdbakei!ppr'lyehr'lyehr'lyehr'lyehbkabei!r'lyehr'lyehr'lyehapkei!kei!ppr'lyehr'lyehr'lyehkaei!ppkei!r'lyehppr'lyehdpdbei!dr'lyehr'lyehr'lyehpei!kei!r'lyehei!pr'lyehkpppkpr'lyehkei!r'lyehr'lyehlpei!r'lyehei!pr'lyehei!pr'lyehpei!pppr'lyehkei!r'lyehr'lyehpppr'lyehr'lyehr'lyehppr'lyehkpei!dpr'lyehr'lyehr'lyehlpkkei!r'lyehr'lyehr'lyehpr'lyehdabbei!ia! ia! ia!pei!ppr'lyehei!r'lyehpr'lyehpppei!ppr'lyehpr'lyehr'lyehr'lyehkabbbei!ia! ia! ia!pei!pr'lyehkei!r'lyehpr'lyehpddr'lyehr'lyehr'lyehr'lyehpbbei!r'lyehr'lyehr'lyehbkaei!ppr'lyehei!kei!r'lyehapkei!kppr'lyehpr'lyehpr'lyehr'lyehpppdddr'lyehr'lyehr'lyehr'lyehabr'lyehr'lyehr'lyehr'lyehkar'lyehdei!pppr'lyehr'lyehbbaei!r'lyehei!kei!r'lyehkkaei!ppr'lyehpr'lyehppdei!pei!pppr'lyehkei!r'lyehei!dlbadei!pr'lyehppr'lyehpr'lyehei!dppei!ppr'lyehpr'lyehr'lyehkapei!r'lyehei!pr'lyehei!pr'lyehpkkpr'lyehdr'lyehr'lyehei!pkei!kadr'lyehr'lyehr'lyehr'lyehbabr'lyehr'lyehei!r'lyehpkei!kpppr'lyehpr'lyehr'lyehpapppr'lyehr'lyehr'lyehr'lyehdbakkpr'lyehr'lyehr'lyehppr'lyehapdddr'lyehr'lyehr'lyehr'lyehdpei!pppr'lyehkei!r'lyehppkei!kpei!pppr'lyehkei!r'lyehppr'lyehppei!kei!r'lyehei!r'lyehabbei!r'lyehei!r'lyehr'lyehpbei!r'lyehr'lyehkei!r'lyehkpei!ppr'lyehei!r'lyehr'lyehpei!pr'lyehr'lyehr'lyehkpbei!r'lyehr'lyehr'lyehr'lyehdpei!ppr'lyehei!kei!r'lyehei!pdppbbbbei!ia! ia! ia!pei!pppr'lyehkei!r'lyehppr'lyehpei!pppr'lyehkei!r'lyehr'lyehpkei!ppr'lyehpr'lyehr'lyehppkpbbei!r'lyehei!r'lyehr'lyehabei!r'lyehei!kei!r'lyehklpbei!r'lyehr'lyehr'lyehr'lyehbkabbbbei!ia! ia! ia!pkppr'lyehr'lyehpr'lyehppr'lyehppapei!ppr'lyehei!r'lyehr'lyehpppr'lyehkei!r'lyehr'lyehr'lyehakei!kppr'lyehr'lyehr'lyehei!pbei!r'lyehei!kei!r'lyehei!pddr'lyehr'lyehr'lyehr'lyehpei!ppr'lyehr'lyehkei!r'lyehklpei!ppr'lyehei!kei!pr'lyehppdei!pei!ppkei!r'lyehei!r'lyehppbei!r'lyehei!kei!r'lyehei!ppbei!r'lyehr'lyehr'lyehbakkpr'lyehr'lyehr'lyehppr'lyehei!dbabei!r'lyehr'lyehr'lyehlpei!ppr'lyehei!kei!pr'lyehpbei!r'lyehei!kei!r'lyehapei!kei!r'lyehei!r'lyehkpkpei!pr'lyehkei!r'lyehr'lyehpbei!kei!r'lyehbbei!r'lyehpei!ppr'lyehei!ppr'lyehei!kei!dei!dpdei!r'lyehdr'lyehr'lyehr'lyehakei!ppr'lyehr'lyehpr'lyehppr'lyehkppei!pr'lyehkei!r'lyehpr'lyehpei!ppkei!r'lyehei!pr'lyehpei!ppr'lyehei!kei!pr'lyehppdei!pbei!kei!r'lyehei!r'lyehp","tag":"chokudAIver2.3.5Div5@12083"}]
EOF
EOM

START_TIME="${SECONDS}"
# Hack for CircleCI.
export PATH="/home/ubuntu/.phpenv/shims:${PATH}"
env
which php
php -v
php "${TEST_SRCDIR}/test/play_icfp2015.php" \
     -c 1 -@x "bash ${PROGRAM1}" -@x "bash ${PROGRAM2}" \
     -@s "${TEST_SRCDIR}/src/sim/sim_main" -t 10 \
     -f "${TEST_SRCDIR}/data/problems/problem_0.json" \
     "${PHRASES[@]}" >"${TMPDIR}/output"
EXPECT_EQ '[{"problemId":0,"seed":0,"tag":"chokudAIver2.2.9@7451","solution":"ia! ia!lei!lbbbbei!aia! ia!lei!lbbbbbbbblablue hadesyuggothei!kbbablue hadesldei!dpppppr'\''lyehpblue hadesei!ddei!ppppkei!dei!dppblue hadesei!r'\''lyehpppppppr'\''lyehbablue hadesei!r'\''lyehkppdlpblue hadesei!r'\''lyehklpblue hadesei!ddei!pppppkklpblue hadesei!r'\''lyehei!kppppablue hadesei!r'\''lyehppppblue hadesei!r'\''lyehdpppblue hadeskppddpppr'\''lyehpppkei!kpblue hadesei!r'\''lyehbdei!kkkei!dppblue hadesei!ddr'\''lyehlpyogsothothppr'\''lyehddayogsothothdpppr'\''lyehkppplanet 10apapblue hadesei!lei!kbblapblue hadesei!r'\''lyehdei!dpppblue hadesei!r'\''lyehppblue hadesei!kei!kbblllkpblue hadesei!r'\''lyehlpblue hadesei!kei!kei!ppppalpplanet 10dei!pkei!dapblue hadesei!kei!kkei!kbldpblue hadesei!pppr'\''lyehppppkpblue hadesldei!ddalpblue hadesei!r'\''lyehpkpppr'\''lyehppblue hadesaddei!ppppr'\''lyehpyogsothothei!apblue hadesei!r'\''lyehppdlpyogsothothei!kei!kbbei!ddbaia! ia!lei!lbbbei!ablue hadesyuggothbablue hadesei!r'\''lyehkkppppppr'\''lyehkpppia! ia!lbbbbbbbei!ablue hadeskppddr'\''lyehpppppkei!kpyogsothothr'\''lyehkppblue hadesei!kei!kei!dei!apblue hadeskppddr'\''lyehpklpblue hadesia! ia!kkppppblue hadesei!kei!kkei!kei!ppppyogsothothr'\''lyehei!kpblue hadesei!r'\''lyehbablue hadesei!kei!kkblapblue hadesei!dblpblue hadesei!ppr'\''lyehkppblue hadesei!kei!kei!kpppapblue hadesei!dei!klapblue hadesei!"}]' "$(cat "${TMPDIR}/output")"

php "${TEST_SRCDIR}/test/play_icfp2015.php" \
     -c 1 -@x "bash ${PROGRAM1}" -@x "bash ${PROGRAM2}" \
     -@s "${TEST_SRCDIR}/src/sim/sim_main" -t 30 \
     -f "${TEST_SRCDIR}/data/problems/problem_0.json" \
     "${PHRASES[@]}" >"${TMPDIR}/output"
EXPECT_EQ '[{"problemId":0,"seed":0,"tag":"chokudAIver2.3.5Div5@12083","solution":"bbei!ia! ia! ia!pbbbbei!ia! ia! ia!apr'\''lyehpr'\''lyehppr'\''lyehppr'\''lyehppdpei!pppr'\''lyehkei!r'\''lyehppr'\''lyehppkyoyodynedpppppppddblue hadesei!pei!ddplanet 10pmonkeyboyabdyuggoththe laundryar'\''lyehkkyogsothothpbbbbtsathogguabddappknecronomiconappr'\''lyehppr'\''lyehr'\''lyehppdei!pei!ppr'\''lyehpr'\''lyehpdappdei!pppr'\''lyehr'\''lyehr'\''lyehpppdpkjohn bigbootedabei!r'\''lyehei!kei!r'\''lyehbbbar'\''lyehkei!r'\''lyehr'\''lyehr'\''lyehppr'\''lyehkpr'\''lyehr'\''lyehr'\''lyehppdpr'\''lyehr'\''lyehr'\''lyehbakei!kkpr'\''lyehr'\''lyehr'\''lyehlpei!ppr'\''lyehei!kei!r'\''lyehkkppr'\''lyehdei!ppr'\''lyehr'\''lyehbbdbakei!ppr'\''lyehr'\''lyehr'\''lyehr'\''lyehbkabei!r'\''lyehr'\''lyehr'\''lyehapkei!kei!ppr'\''lyehr'\''lyehr'\''lyehkaei!ppkei!r'\''lyehppr'\''lyehdpdbei!dr'\''lyehr'\''lyehr'\''lyehpei!kei!r'\''lyehei!pr'\''lyehkpppkpr'\''lyehkei!r'\''lyehr'\''lyehlpei!r'\''lyehei!pr'\''lyehei!pr'\''lyehpei!pppr'\''lyehkei!r'\''lyehr'\''lyehpppr'\''lyehr'\''lyehr'\''lyehppr'\''lyehkpei!dpr'\''lyehr'\''lyehr'\''lyehlpkkei!r'\''lyehr'\''lyehr'\''lyehpr'\''lyehdabbei!ia! ia! ia!pei!ppr'\''lyehei!r'\''lyehpr'\''lyehpppei!ppr'\''lyehpr'\''lyehr'\''lyehr'\''lyehkabbbei!ia! ia! ia!pei!pr'\''lyehkei!r'\''lyehpr'\''lyehpddr'\''lyehr'\''lyehr'\''lyehr'\''lyehpbbei!r'\''lyehr'\''lyehr'\''lyehbkaei!ppr'\''lyehei!kei!r'\''lyehapkei!kppr'\''lyehpr'\''lyehpr'\''lyehr'\''lyehpppdddr'\''lyehr'\''lyehr'\''lyehr'\''lyehabr'\''lyehr'\''lyehr'\''lyehr'\''lyehkar'\''lyehdei!pppr'\''lyehr'\''lyehbbaei!r'\''lyehei!kei!r'\''lyehkkaei!ppr'\''lyehpr'\''lyehppdei!pei!pppr'\''lyehkei!r'\''lyehei!dlbadei!pr'\''lyehppr'\''lyehpr'\''lyehei!dppei!ppr'\''lyehpr'\''lyehr'\''lyehkapei!r'\''lyehei!pr'\''lyehei!pr'\''lyehpkkpr'\''lyehdr'\''lyehr'\''lyehei!pkei!kadr'\''lyehr'\''lyehr'\''lyehr'\''lyehbabr'\''lyehr'\''lyehei!r'\''lyehpkei!kpppr'\''lyehpr'\''lyehr'\''lyehpapppr'\''lyehr'\''lyehr'\''lyehr'\''lyehdbakkpr'\''lyehr'\''lyehr'\''lyehppr'\''lyehapdddr'\''lyehr'\''lyehr'\''lyehr'\''lyehdpei!pppr'\''lyehkei!r'\''lyehppkei!kpei!pppr'\''lyehkei!r'\''lyehppr'\''lyehppei!kei!r'\''lyehei!r'\''lyehabbei!r'\''lyehei!r'\''lyehr'\''lyehpbei!r'\''lyehr'\''lyehkei!r'\''lyehkpei!ppr'\''lyehei!r'\''lyehr'\''lyehpei!pr'\''lyehr'\''lyehr'\''lyehkpbei!r'\''lyehr'\''lyehr'\''lyehr'\''lyehdpei!ppr'\''lyehei!kei!r'\''lyehei!pdppbbbbei!ia! ia! ia!pei!pppr'\''lyehkei!r'\''lyehppr'\''lyehpei!pppr'\''lyehkei!r'\''lyehr'\''lyehpkei!ppr'\''lyehpr'\''lyehr'\''lyehppkpbbei!r'\''lyehei!r'\''lyehr'\''lyehabei!r'\''lyehei!kei!r'\''lyehklpbei!r'\''lyehr'\''lyehr'\''lyehr'\''lyehbkabbbbei!ia! ia! ia!pkppr'\''lyehr'\''lyehpr'\''lyehppr'\''lyehppapei!ppr'\''lyehei!r'\''lyehr'\''lyehpppr'\''lyehkei!r'\''lyehr'\''lyehr'\''lyehakei!kppr'\''lyehr'\''lyehr'\''lyehei!pbei!r'\''lyehei!kei!r'\''lyehei!pddr'\''lyehr'\''lyehr'\''lyehr'\''lyehpei!ppr'\''lyehr'\''lyehkei!r'\''lyehklpei!ppr'\''lyehei!kei!pr'\''lyehppdei!pei!ppkei!r'\''lyehei!r'\''lyehppbei!r'\''lyehei!kei!r'\''lyehei!ppbei!r'\''lyehr'\''lyehr'\''lyehbakkpr'\''lyehr'\''lyehr'\''lyehppr'\''lyehei!dbabei!r'\''lyehr'\''lyehr'\''lyehlpei!ppr'\''lyehei!kei!pr'\''lyehpbei!r'\''lyehei!kei!r'\''lyehapei!kei!r'\''lyehei!r'\''lyehkpkpei!pr'\''lyehkei!r'\''lyehr'\''lyehpbei!kei!r'\''lyehbbei!r'\''lyehpei!ppr'\''lyehei!ppr'\''lyehei!kei!dei!dpdei!r'\''lyehdr'\''lyehr'\''lyehr'\''lyehakei!ppr'\''lyehr'\''lyehpr'\''lyehppr'\''lyehkppei!pr'\''lyehkei!r'\''lyehpr'\''lyehpei!ppkei!r'\''lyehei!pr'\''lyehpei!ppr'\''lyehei!kei!pr'\''lyehppdei!pbei!kei!r'\''lyehei!r'\''lyehp"}]' "$(cat "${TMPDIR}/output")"
