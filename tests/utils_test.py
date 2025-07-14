# -*- coding: utf-8 -*-
#
# This file is part of reana.
# Copyright (C) 2019 CERN.
#
# REANA is free software; you can redistribute it and/or modify it
# under the terms of the MIT License; see LICENSE file for more details.


import filecmp
import os
import subprocess as sp
import urllib.request as ur

from cms_reco.utils import (load_config_from_cod,
                            remove_additionally_generated_files,
                            remove_folder)


def generate_file(recid, directory, workflow_engine, config_file):
    """Generate the reana.yaml using the workflow factory."""

    load_config_from_cod(recid, config_file=f"{config_file}")

    sp.call(f"cms-reco  create-workflow --directory {directory}"
            f" --workflow_engine {workflow_engine}"
            f" --config_file {config_file}",
            shell=True)

    workflow_file = None
    if workflow_engine == "serial":
        workflow_file = f"{directory}/reana.yaml"
    elif workflow_engine == "cwl":
        workflow_file = f"{directory}/workflow/reco.cwl"

    if os.path.isfile(workflow_file):
        return workflow_file
    else:
        return None


def download_existing_file(url, local_file_name='reference.yaml'):
    """Get a well known and working reana.yaml workflow file."""
    ur.urlretrieve(url, local_file_name)
    return local_file_name


def compare_files(ref_file, gen_file):
    """Compare two files for their content."""
    return filecmp.cmp(ref_file, "{0}".format(gen_file), shallow=False)


def workflow_test(reference_repo, recid, local_file_name="reference.yaml",
                  workflow_engine="serial", to_delete=True, tmp_folder="tmp"):
    """Test template."""
    try:
        config_file = f"config.json"
        ref_file = download_existing_file(
            reference_repo,
            local_file_name=local_file_name)

        gen_file = generate_file(config_file=config_file,
                                 recid=recid, directory=tmp_folder,
                                 workflow_engine=workflow_engine)

        if not ref_file:
            raise Exception("Reference file not downloaded.")
        elif not gen_file:
            raise Exception("Workflow not generated from factory.")

        assert compare_files(ref_file, gen_file)

    finally:
        if to_delete:
            remove_additionally_generated_files([ref_file, config_file])

            remove_folder(tmp_folder)
