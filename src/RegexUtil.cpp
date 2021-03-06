/*
	Copyright 2009-2012, Sumeet Chhetri

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/
/*
 * RegexUtil.cpp
 *
 *  Created on: 14-Aug-2012
 *      Author: sumeetc
 */

#include "RegexUtil.h"

//map<string, regex_t> RegexUtil::patterns;

RegexUtil::RegexUtil() {
	// TODO Auto-generated constructor stub

}

RegexUtil::~RegexUtil() {
	// TODO Auto-generated destructor stub
}

void RegexUtil::find(const string& text, const string& pattern, int &spos, int &epos, bool matchNewLine/* = false*/)
{
	string ttext(text);
	regex_t regex;
	int reti;
	/*if(patterns.find(pattern)!=patterns.end())
	{
		regex = patterns[pattern];
	}
	else*/
	{
		/* Compile regular expression */
		int cflags = REG_EXTENDED;
		if(matchNewLine)
			cflags = REG_NEWLINE | REG_EXTENDED;

		reti = regcomp(&regex, pattern.c_str(), cflags);
		if(reti)
		{
			cout << ("Could not compile regex - "+pattern) << endl;
		}
		else
		{
			//patterns[pattern] = regex;
		}
	}
	spos = -1;
	epos = -1;
	regmatch_t pm;
	reti = regexec(&regex, ttext.c_str(), 1, &pm, 0);
	regfree(&regex);
	if (reti == 0) {    /* while matches found */
		/* substring found between pm.rm_so and pm.rm_eo */
		/* This call to regexec() finds the next match */
		spos = pm.rm_so;
		epos = pm.rm_eo;
	}
}

int RegexUtil::find(const string& text, const string& pattern, bool matchNewLine/* = false*/)
{
	string ttext(text);
	regex_t regex;
	int reti;
	/*if(patterns.find(pattern)!=patterns.end())
	{
		regex = patterns[pattern];
	}
	else*/
	{
		/* Compile regular expression */
		int cflags = REG_EXTENDED;
		if(matchNewLine)
			cflags = REG_NEWLINE | REG_EXTENDED;

		reti = regcomp(&regex, pattern.c_str(), cflags);
		if(reti)
		{
			cout << ("Could not compile regex - "+pattern) << endl;
		}
		else
		{
			//patterns[pattern] = regex;
		}
	}
	regmatch_t pm;
	reti = regexec(&regex, ttext.c_str(), 1, &pm, 0);
	regfree(&regex);
	if (reti == 0) {    /* while matches found */
		/* substring found between pm.rm_so and pm.rm_eo */
		/* This call to regexec() finds the next match */
		return pm.rm_so;
	}
	return -1;
}

vector<string> RegexUtil::search(const string& text, const string& pattern, bool matchNewLine/* = false*/) {
	vector<string> vec;
	string ttext(text);
	regex_t regex;
	int reti;
	/*if(patterns.find(pattern)!=patterns.end())
	{
		regex = patterns[pattern];
	}
	else*/
	{
		/* Compile regular expression */
		int cflags = REG_EXTENDED;
		if(matchNewLine)
			cflags = REG_NEWLINE | REG_EXTENDED;

		reti = regcomp(&regex, pattern.c_str(), cflags);
		if(reti)
		{
			cout << ("Could not compile regex - "+pattern) << endl;
		}
		else
		{
			//patterns[pattern] = regex;
		}
	}
	regmatch_t pm;
	reti = regexec(&regex, ttext.c_str(), 1, &pm, 0);
	while (reti == 0) {    /* while matches found */
		/* substring found between pm.rm_so and pm.rm_eo */
		/* This call to regexec() finds the next match */
		if(!reti) {
			string match;
			match = ttext.substr(pm.rm_so, pm.rm_eo-pm.rm_so);
			vec.push_back(match);
		} else {
			break;
		}
		ttext = ttext.substr(pm.rm_eo);
		pm.rm_eo = -1;
		pm.rm_so = -1;
		reti = regexec (&regex, ttext.c_str(), 1, &pm, 0);
	}
	regfree(&regex);
	return vec;
}

string RegexUtil::replaceCopy(const string& text, const string& pattern, const string& with, bool matchNewLine/* = false*/) {
	string ttext(text);
	string rettxt;
	regex_t regex;
	int reti;
	/*if(patterns.find(pattern)!=patterns.end())
	{
		regex = patterns[pattern];
	}
	else*/
	{
		/* Compile regular expression */
		int cflags = REG_EXTENDED;
		if(matchNewLine)
			cflags = REG_NEWLINE | REG_EXTENDED;

		reti = regcomp(&regex, pattern.c_str(), cflags);
		if(reti)
		{
			cout << ("Could not compile regex - "+pattern) << endl;
		}
		else
		{
			//patterns[pattern] = regex;
		}
	}
	regmatch_t pm;
	reti = regexec(&regex, ttext.c_str(), 1, &pm, 0);
	while (reti == 0) {    /* while matches found */
		/* substring found between pm.rm_so and pm.rm_eo */
		/* This call to regexec() finds the next match */
		if(!reti) {
			string match;
			match = ttext.substr(pm.rm_so, pm.rm_eo-pm.rm_so);
			rettxt += ttext.substr(0, pm.rm_so) + with;
		} else {
			rettxt += ttext;
			break;
		}
		ttext = ttext.substr(pm.rm_eo);
		pm.rm_eo = -1;
		pm.rm_so = -1;
		reti = regexec (&regex, ttext.c_str(), 1, &pm, 0);
	}
	regfree(&regex);
	if(ttext!="")rettxt += ttext;

	if(text!=rettxt)
	{
		while(replace(rettxt, pattern, with, matchNewLine)) {}
	}
	return rettxt;
}

bool RegexUtil::replace(string& text, const string& pattern, const string& with, bool matchNewLine/* = false*/) {
	string ttext(text);
	string rettxt;
	regex_t regex;
	int reti;
	/*if(patterns.find(pattern)!=patterns.end())
	{
		regex = patterns[pattern];
	}
	else*/
	{
		/* Compile regular expression */
		int cflags = REG_EXTENDED;
		if(matchNewLine)
			cflags = REG_NEWLINE | REG_EXTENDED;

		reti = regcomp(&regex, pattern.c_str(), cflags);
		if(reti)
		{
			cout << ("Could not compile regex - "+pattern) << endl;
		}
		else
		{
			//patterns[pattern] = regex;
		}
	}
	regmatch_t pm;
	reti = regexec(&regex, ttext.c_str(), 1, &pm, 0);
	while (reti == 0) {    /* while matches found */
		/* substring found between pm.rm_so and pm.rm_eo */
		/* This call to regexec() finds the next match */
		if(!reti) {
			string match;
			match = ttext.substr(pm.rm_so, pm.rm_eo-pm.rm_so);
			rettxt += ttext.substr(0, pm.rm_so) + with;
		} else {
			rettxt += ttext;
			break;
		}
		ttext = ttext.substr(pm.rm_eo);
		pm.rm_eo = -1;
		pm.rm_so = -1;
		reti = regexec (&regex, ttext.c_str(), 1, &pm, 0);
	}
	regfree(&regex);
	if(ttext!="")rettxt += ttext;
	if(text==rettxt)
		return false;
	text = rettxt;
	while(replace(text, pattern, with, matchNewLine)) {}
	return true;
}
