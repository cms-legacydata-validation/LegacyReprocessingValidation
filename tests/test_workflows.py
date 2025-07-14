# -*- coding: utf-8 -*-
#
# This file is part of reana.
# Copyright (C) 2019, 2023 CERN.
#
# REANA is free software; you can redistribute it and/or modify it
# under the terms of the MIT License; see LICENSE file for more details.


from utils_test import workflow_test


def test_2010_jet_serial():
    reference_repo = 'https://raw.githubusercontent.com/' \
                     'dprelipcean/reana-demo-cms-reco/' \
                     'reana_example_2010/reana.yaml'

    workflow_test(recid=45, reference_repo=reference_repo,
                  local_file_name="reana_serial.yaml",
                  workflow_engine="serial",
                  to_delete=True, tmp_folder="tmp_2010_jet_serial")


def test_2011_doubleelectron_serial():
    reference_repo = 'https://raw.githubusercontent.com/' \
                     'dprelipcean/reana-demo-cms-reco/' \
                     'reana_example_2011/reana.yaml'

    workflow_test(recid=46, reference_repo=reference_repo,
                  local_file_name="reana_serial.yaml",
                  workflow_engine="serial",
                  to_delete=True, tmp_folder="tmp_2011_de_serial")


def test_2012_singlemu_serial():
    reference_repo = 'https://raw.githubusercontent.com/' \
                     'dprelipcean/reana-demo-cms-reco/' \
                     'reana_example_2012/reana.yaml'

    workflow_test(recid=63, reference_repo=reference_repo,
                  local_file_name="reana_serial.yaml",
                  workflow_engine="serial",
                  to_delete=True, tmp_folder="tmp_2012_singlemu_serial")


def test_2010_jet_cwl():
    reference_repo = 'https://raw.githubusercontent.com/' \
                     'dprelipcean/reana-demo-cms-reco/' \
                     'reana_example_2010/workflow/reco.cwl'

    workflow_test(recid=45, reference_repo=reference_repo,
                  local_file_name="reana_cwl.yaml",
                  workflow_engine="cwl",
                  to_delete=True, tmp_folder="tmp_2010_de_cwl")


def test_2011_doubleelectron_cwl():
    reference_repo = 'https://raw.githubusercontent.com/' \
                     'dprelipcean/reana-demo-cms-reco/' \
                     'reana_example_2011/workflow/reco.cwl'

    workflow_test(recid=46, reference_repo=reference_repo,
                  local_file_name="reana_cwl.yaml",
                  workflow_engine="cwl",
                  to_delete=True, tmp_folder="tmp_2011_de_cwl")


def test_2012_singlemu_cwl():
    reference_repo = 'https://raw.githubusercontent.com/' \
                     'dprelipcean/reana-demo-cms-reco/' \
                     'reana_example_2012/workflow/reco.cwl'

    workflow_test(recid=63, reference_repo=reference_repo,
                  local_file_name="reana_cwl.yaml",
                  workflow_engine="cwl",
                  to_delete=True, tmp_folder="tmp_2012_singlemu_cwl")
