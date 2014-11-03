
#include <stdio.h>
#include <string>
#include "lib/sqlhelper.h"
#include "SQLParser.h"

using namespace hsql;

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        fprintf(stderr, "No SQL-Statement given!\n");
        return -1;
    }

    for (int n = 1; n < argc; ++n) {
        char* sql = argv[n];

        printf("\nEvaluating Statement \"%s\"\n", sql);
        Statement* stmt = SQLParser::parseSQLString(sql);

        if (stmt == NULL) {
        	fprintf(stderr, "Parsing of \"%s\" failed!\n", sql);
        	continue;
        }

        if (stmt->type == kStmtSelect) {
        	printSelectStatementInfo((SelectStatement*) stmt, 0);
        } else if (stmt->type == kStmtJoin) {
            printJoinStatementInfo((JoinStatement*) stmt, 0);
        } else {
            if (stmt->type == kStmtError) {
                fprintf(stderr, "%s!\n", stmt->parser_msg);
            } else {
                fprintf(stderr, "Unsupported Statement Type %u!\n", stmt->type);
            }
		}
    }

	return 0;
}