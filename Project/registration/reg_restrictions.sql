CREATE TABLE IF NOT EXISTS reg_student_holds(
    cnetid VARCHAR(32),
    hold_type VARCHAR(32)
    PRIMARY KEY (cnetid, hold_type)
);
